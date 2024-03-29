#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

#include <vk_mem_alloc.h>

#include <cstring>

#include "../include/core/defines/defines.h"
#include "core/defines/basic_defines.h"
#include "glyphs.h"
#include "rendering/window.h"

struct Texture_Atlas
{
  public:
    friend class VK_Renderer;
    static constexpr uint32_t texture_limit()
    {
        return 1 << 16;
    }

    void attachRenderComponents(VkDevice *device, VkQueue *graphicsqueue, VkCommandPool *commandPool,
                                VmaAllocator *allocator, bool *FrameBufferNeedsReconstruction);

    void createTextureSampler();

    // replaces the old texture with the new one
    void changeTextureAtIndex(size_t index, Empaerior::byte *pixels, Empaerior::u_int width, Empaerior::u_int height);

    size_t create_texture_from_file(const std::string &path);
    [[nodiscard]] size_t create_texture_from_memory(Empaerior::byte *pixels, Empaerior::u_int width,
                                                    Empaerior::u_int height, Empaerior::s_int texChannels);

    size_t create_texture_from_fontPath(Empaerior::Font &font, const std::string &path, Empaerior::u_int size);
    size_t getFont(const char *path);

    size_t getImageSize(size_t index);

    // destroy image at index
    void destroyImage(size_t index);

    // create an image at index index, throws if there's already a image there
    // asumems pixels is valid
    void createImageAtIndex(size_t index, Empaerior::byte *pixels, Empaerior::u_int width, Empaerior::u_int height);

    void cleanup();

    std::vector<Empaerior::Point2f> image_dimensions;

  private:
    VkDevice *m_device;
    VkQueue *m_graphicsqueue;
    VkCommandPool *m_commandpool;
    VmaAllocator *m_allocator;
    bool *framebufferResetSwitch;

    std::vector<VmaAllocation> image_allocations;
    std::vector<VkImage> images;
    std::vector<VkImageView> image_views;

    std::unordered_map<std::string, Empaerior::u_inter> fontName;
    std::unordered_map<std::string, Empaerior::u_inter> texturePath;

    VkSampler textureSampler;
};
