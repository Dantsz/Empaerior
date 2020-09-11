#pragma once

#include <vulkan/vulkan.h>

#include <vector>
#include <string>


#include <vk_mem_alloc.h>

#include <cstring>

#include "../include/core/defines/defines.h"
#include "glyphs.h"

 

    


struct Texture_Atlas {

    static constexpr uint32_t texture_limit()
    {
        return 1 << 16;
    }


    void attachRenderComponents(VkDevice* device, VkQueue* graphicsqueue, VkCommandPool* commandPool, VmaAllocator* allocator, bool* FrameBufferNeedsReconstruction);
   
    void createTextureSampler();

    size_t create_texture_from_file(const std::string& path);
    size_t create_texture_from_memory(Empaerior::byte* pixels, Empaerior::s_int width, Empaerior::s_int height, Empaerior::s_int texChannels);
   

    size_t create_texture_from_fontPath(Empaerior::Font& font, const std::string& path, Empaerior::u_int size);
    size_t getFont(const char* path);
    


    void cleanup();


    VkDevice* m_device;
    VkQueue* m_graphicsqueue;
    VkCommandPool* m_commandpool;
    VmaAllocator* m_allocator;
    bool* framebufferResetSwitch;

    std::vector<VmaAllocation> image_allocations;
    std::vector<VkImage> images;
    std::vector<VkImageView> image_views;



    std::vector<Empaerior::Point2f> image_dimensions;


    std::unordered_map<std::string, Empaerior::u_inter> fontName;
    std::unordered_map<std::string, Empaerior::u_inter> texturePath;

    VkSampler textureSampler;
};