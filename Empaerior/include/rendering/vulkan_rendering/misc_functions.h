#pragma once
#include <vulkan/vulkan.h>
#include "../../../include/core/defines/defines.h"
#include <vk_mem_alloc.h>

namespace Empaerior {

	namespace VKfunctions
	{
		VkCommandBuffer beginSingleTimeCommands(VkDevice& device, VkQueue& graphicsQueue, VkCommandPool& commandPool);
		void endSingleTimeCommands(VkDevice& device, VkQueue& graphicsQueue, VkCommandPool& commandPool, VkCommandBuffer commandBuffer);

		void allocateBuffer(VmaAllocator& allocator, VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer, VmaAllocation& allocation, VmaAllocationCreateInfo& allocInfo);
		void copyBuffer(VkDevice device, VkQueue graphicsQueue, VkCommandPool commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

		void createImage(VmaAllocator& allocator, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VmaAllocation& allocation);
		void transitionImageLayout(VkDevice& device, VkQueue& graphicsQueue, VkCommandPool& commandPool, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		void copyBufferToImage(VkDevice& device, VkQueue& graphicsQueue, VkCommandPool& commandPool, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

		VkImageView createImageView(VkDevice& device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	}
}