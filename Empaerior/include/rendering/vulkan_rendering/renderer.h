#pragma once

#include <vulkan/vulkan.h>


#include <vector>
#include <SDL.h>
#include "camera.h"
#include <vk_mem_alloc.h>
#include "../include/core/defines/defines.h"
#include "geometry_buffer.h"
#include "texture_atlas.h"
#include "graphic_settings.h"
#include <functional>

#include "../include/rendering/window.h"

const inline int MAX_FRAMES_IN_FLIGHT = 2;
const inline std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation",


};

const inline std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
};

#ifdef EMP_USE_LOGS
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif




class VK_Renderer {
public:
    void Init(Empaerior::Window* window);
    void checkFrameBufferResize();

  

    void cleanup();

   
  /*
        Packs all functions fr rendering th frame in one
    */
    EMP_FORCEINLINE void renderFrame(){
        
        if (framebufferNeedsReconstruction)
		{
			checkFrameBufferResize();	
			framebufferNeedsReconstruction = false;
		}
        newFrame();
		drawFrame();
		present();
    }
    /*
    The frameBufferRecF function is called when the frame buffer needs to be reconstructed
    The renderF function is called in between preparing a new frame and rendering
    */
    void renderFrame(std::function<void()> frameBufferRecF , std::function<void()> renderF)
    {
        if (framebufferNeedsReconstruction)
		{
			checkFrameBufferResize();
            frameBufferRecF();	
			framebufferNeedsReconstruction = false;
		}
        newFrame();
        renderF();
		drawFrame();
		present();
    }
   

 

    Texture_Atlas texture_atlas;

    SDL_Window* sdl_window;


    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;
    VkSurfaceFormatKHR surfaceFormat;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;

    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;


    VkImage depthImage;
    VmaAllocation depthImageAllocation;
    VkImageView depthImageView;




    VkRenderPass renderPass;

    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    VkCommandPool commandPool;
    geometryBuffer geometrybuffer;


    VkResult Presentresult;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VmaAllocation> uniformBuffersAllocations;
    std::vector<void*> uniformBufferData;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame = 0;

    VmaAllocator allocator;

  

    std::vector<VkCommandBuffer> inUseCommandBuffers;
    size_t mainCommandBufferinUseIndex;

    Empaerior::VK_RendererGraphicsInfo GraphicsSettings, InitialGraphicsSettings;

   
    Empaerior::Camera2D ubo{};

    uint32_t imageIndex;
    bool framebufferNeedsReconstruction = false;
private:


    


    void initVulkan();


    void recreateSwapChain();

    void cleanupSwapChain();


    void createDepthResources();

  
    void createInstance();

   

    void createLogicalDevice();


    void createAllocator();

    void createSwapChain();

    void createRenderPass();

    void createDescriptorPool();

    void createDescriptorSetLayout();

    void createDescriptorSets();

    void updateDescriptorSets();

    void createGraphicsPipeline(Empaerior::VK_RendererGraphicsInfo& info);

    void createFramebuffers();

    void createCommandPool();


    void createImageViews();


    void createCommandBuffers();

    void recordCommandBuffer(VkCommandBuffer& commandBuffer, VkFramebuffer& swapChainFramebuffer, VkBuffer vertexBuffers[], VkBuffer& indexBuffer, VkDescriptorSet* descriptorSet);

    void createSyncObjects();

    void createUniformBuffers();

    void updateUniformBuffer(uint32_t currentImage);

    void newFrame();

    void drawFrame();

    void present();
  
    
};