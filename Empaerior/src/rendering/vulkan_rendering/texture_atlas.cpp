#include "..\..\..\include\rendering\vulkan_rendering\texture_atlas.h"
#include <stb_image.h>
#include "..\..\..\include\rendering\vulkan_rendering\misc_functions.h"

void Texture_Atlas::attachRenderComponents(VkDevice* device, VkQueue* graphicsqueue, VkCommandPool* commandPool, VmaAllocator* allocator)
{
    m_device = device;
    m_graphicsqueue = graphicsqueue;
    m_commandpool = commandPool;
    m_allocator = allocator;

}

size_t Texture_Atlas::create_texture_from_file(const std::string& path, bool& implementUpdate)
{


    Empaerior::s_int texWidth, texHeight, texChannels;
    stbi_uc* pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    if (!pixels) {
        ENGINE_CRITICAL(std::string("Failed to load texture : " + path)); return 0;
    }
    return  create_texture_from_memory(pixels, texWidth, texHeight, texChannels, implementUpdate);


}

size_t Texture_Atlas::create_texture_from_memory(Empaerior::byte* pixels, Empaerior::s_int width, Empaerior::s_int height, Empaerior::s_int texChannels, bool& implementUpdate)
{
    image_allocations.push_back({});
    images.push_back({});
    image_dimensions.push_back({ static_cast<Empaerior::fl_point>(width),static_cast<Empaerior::fl_point>(height) });
    VkDeviceSize imageSize = width * height * 4;

    if (!pixels) {
        throw std::runtime_error("invalid image");
    }
    VkBuffer stagingBuffer;


    VmaAllocation buffer_allocation;

    VmaAllocationCreateInfo allocInfo{};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    allocInfo.requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    allocateBuffer(*m_allocator, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, stagingBuffer, buffer_allocation, allocInfo);
    void* data;

    vmaMapMemory(*m_allocator, buffer_allocation, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vmaUnmapMemory(*m_allocator, buffer_allocation);





    createImage(*m_allocator, width, height, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, images[images.size() - 1], image_allocations[image_allocations.size() - 1]);

    transitionImageLayout(*m_device, *m_graphicsqueue, *m_commandpool, images[images.size() - 1], VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    copyBufferToImage(*m_device, *m_graphicsqueue, *m_commandpool, stagingBuffer, images[images.size() - 1], static_cast<uint32_t>(width), static_cast<uint32_t>(height));
    transitionImageLayout(*m_device, *m_graphicsqueue, *m_commandpool, images[images.size() - 1], VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);


    vmaDestroyBuffer(*m_allocator, stagingBuffer, buffer_allocation);

    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = images[images.size() - 1];
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    image_views.push_back({});
    if (vkCreateImageView(*m_device, &viewInfo, nullptr, &image_views[image_views.size() - 1]) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture image view!");
    }

    implementUpdate = true;
    return images.size() - 1;

}

size_t Texture_Atlas::create_texture_from_fontPath(Empaerior::Font& font, char* path, Empaerior::u_int size, bool& implementUpdate)
{

    Empaerior::FontLoading::createFontFacefrompath(font, path);
    Empaerior::FontLoading::setFontSize(font, size);
    Empaerior::FontLoading::createFontTexture(font);

    size_t ftextIndex = create_texture_from_memory(font.fontTexture.data(), font.texWidth, font.texHeight, 0, implementUpdate);
    fontName.insert({ path , ftextIndex });
    return ftextIndex;

}

size_t Texture_Atlas::getFont(const char* path)
{
    auto fontID = fontName.find(path);
    if (fontID == fontName.end())
    {
        ENGINE_WARN("The specified font does not exist");
        return -1;
    }
    return fontID->second;
}

void Texture_Atlas::cleanup()
{

    for (size_t i = 0; i < images.size(); i++)
    {
        vkDestroyImageView(*m_device, image_views[i], nullptr);
        vmaDestroyImage(*m_allocator, images[i], image_allocations[i]);
    }
}
