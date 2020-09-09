#pragma once

#include "imgui-master/imgui.h"
#include "imgui-empaerior/imgui_impl_vulkan.h"
#include "imgui-empaerior/imgui_empaerior.h"
#include <Empaerior.h>
#include <rendering/vulkan_rendering/renderer.h>
#include <optional>
/*
	

*/
namespace ImGui_Emp
{
	
	static inline VkRenderPass imguiRenderPass;
	static inline std::vector<ImGui_ImplVulkanH_Frame> Frames;
	static inline size_t imguiCommandBufferIndex;
	static inline ImGui_ImplVulkanH_Window wd;

	struct QueueFamilyIndices {

		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};
	
	//Initialize EMP_IMGui
	//if you're using the sdl_render this should be called after the renderer is attached to the window

	static QueueFamilyIndices findQueueFamilies(VkSurfaceKHR& surface, VkPhysicalDevice device) {
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

			if (presentSupport) {
				indices.presentFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}

	static void CreateRenderPass(VK_Renderer& renderer)
	{

		VkAttachmentDescription colorAttachment{};
		colorAttachment.format = renderer.swapChainImageFormat;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;// don't clear the screen please , thanks
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef = {};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;



		VkSubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;





		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;


		std::array<VkAttachmentDescription, 1> attachments = { colorAttachment };
		VkRenderPassCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.attachmentCount = attachments.size();
		info.pAttachments = attachments.data();
		info.subpassCount = 1;
		info.pSubpasses = &subpass;
		info.dependencyCount = 1;
		info.pDependencies = &dependency;

		if (vkCreateRenderPass(renderer.device, &info, nullptr, &imguiRenderPass) != VK_SUCCESS) {
			throw std::runtime_error("Could not create Dear ImGui's render pass");
		}

	}
	
	static void CreateCommandObjects(VK_Renderer& renderer)
	{
		
		for (size_t i = 0; i < renderer.swapChainImages.size(); i++)
		{
			QueueFamilyIndices queueFamilyIndices = findQueueFamilies(renderer.surface , renderer.physicalDevice);
			VkCommandPoolCreateInfo poolInfo{};
			poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
			poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			if (vkCreateCommandPool(renderer.device, &poolInfo, nullptr, &Frames[i].CommandPool) != VK_SUCCESS) {
				throw std::runtime_error("failed to create graphics command pool!");
			}

			VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
			commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			commandBufferAllocateInfo.commandPool = Frames[i].CommandPool;
			commandBufferAllocateInfo.commandBufferCount = 1;
			vkAllocateCommandBuffers(renderer.device, &commandBufferAllocateInfo, &Frames[i].CommandBuffer);



		}
	}
	static void CreateFrameBuffers(Empaerior::Window& window, VK_Renderer& renderer)
	{
		for (uint32_t i = 0; i < renderer.swapChainImages.size(); i++)
		{
			VkImageView attachment[1];
			VkFramebufferCreateInfo FBinfo = {};
			FBinfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			FBinfo.renderPass = imguiRenderPass;
			FBinfo.attachmentCount = 1;
			FBinfo.pAttachments = attachment;
			FBinfo.width = window.get_width();
			FBinfo.height = window.get_heigth();
			
			FBinfo.layers = 1;

			ImGui_ImplVulkanH_Frame* fd = &Frames[i];
			attachment[0] = renderer.swapChainImageViews[i];

			if (vkCreateFramebuffer(renderer.device, &FBinfo, nullptr, &fd->Framebuffer) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed creating IMGUI FrameBuffer");
			}

		}
	}

	static void AttachImgui(Empaerior::Window& window, VK_Renderer& renderer)
	{
		wd.Swapchain = renderer.swapChain;
		wd.Surface = renderer.surface;
		wd.SurfaceFormat = renderer.surfaceFormat;
		wd.ImageCount = renderer.swapChainImages.size();

		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = renderer.instance;
		init_info.PhysicalDevice = renderer.physicalDevice;
		init_info.Device = renderer.device;
		init_info.QueueFamily = VK_QUEUE_GRAPHICS_BIT;
		init_info.Queue = renderer.graphicsQueue;
		init_info.PipelineCache = VK_NULL_HANDLE;
		init_info.DescriptorPool = renderer.descriptorPool;
		init_info.Allocator = nullptr;
		init_info.MinImageCount = renderer.swapChainImages.size();
		init_info.ImageCount = renderer.swapChainImages.size();
		init_info.CheckVkResultFn = nullptr;





		CreateRenderPass(renderer);


		//

		Frames.resize(renderer.swapChainImages.size());

		CreateCommandObjects(renderer);


		CreateFrameBuffers(window, renderer);
		

		ImGui_ImplVulkan_Init(&init_info, imguiRenderPass);

		//insert commandBuffer 
		renderer.inUseCommandBuffers.push_back({});
		imguiCommandBufferIndex = renderer.inUseCommandBuffers.size() - 1;


		VkCommandBuffer command_buffer = Empaerior::VKfunctions::beginSingleTimeCommands(renderer.device, renderer.graphicsQueue, renderer.commandPool);
		ImGui_ImplVulkan_CreateFontsTexture(command_buffer);
		Empaerior::VKfunctions::endSingleTimeCommands(renderer.device, renderer.graphicsQueue, renderer.commandPool, command_buffer);

	}
	static void DettachImgui(Empaerior::Window& window, VK_Renderer& renderer)
	{

		for (uint32_t i = 0; i < renderer.swapChainImages.size(); i++)
		{
			vkDestroyFramebuffer(renderer.device, Frames[i].Framebuffer, nullptr);
		}


		for (size_t i = 0; i < renderer.swapChainImages.size(); i++)
		{
			vkFreeCommandBuffers(renderer.device, Frames[i].CommandPool, 1, &Frames[i].CommandBuffer);
			vkDestroyCommandPool(renderer.device, Frames[i].CommandPool, nullptr);
		
		}

	
		vkDestroyRenderPass(renderer.device, imguiRenderPass, nullptr);
		ImGui_ImplVulkan_Shutdown();
		renderer.inUseCommandBuffers.erase(renderer.inUseCommandBuffers.begin() + imguiCommandBufferIndex);
	}


	EMP_FORCEINLINE void Init( Empaerior::Window& window , VK_Renderer& renderer)
	{

		ImGui::CreateContext();
		

		
		
		ImGuiEmpImpl::Init(Empaerior::Application::window);


	

		AttachImgui(window, renderer);

	
	
	
	}

	EMP_FORCEINLINE void NewFrame(Empaerior::Window& window,VK_Renderer& renderer)
	{
	
		ImGui_ImplVulkan_NewFrame();


		ImGuiEmpImpl::NewFrame(Empaerior::Application::window);
		ImGui::NewFrame();
	}


	



	EMP_FORCEINLINE void Render(Empaerior::Window& window, VK_Renderer& renderer)
	{
	
		ImGui::Render();
		ImGui_ImplVulkanH_Frame* fd = &Frames[renderer.imageIndex];
		
		//auto err = vkResetCommandPool(renderer.device, fd->CommandPool, 0);
		vkResetCommandBuffer(fd->CommandBuffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

		VkCommandBufferBeginInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		
		

		std::array<VkClearValue, 1> clearValues{};
		clearValues[0].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		//clearValues[1].depthStencil = { 1.0f, 0 };

		VkRenderPassBeginInfo renderInfo;

		renderInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	
		renderInfo.renderPass = imguiRenderPass;
		renderInfo.framebuffer = fd->Framebuffer;
		renderInfo.renderArea.offset = { 0, 0 };
		renderInfo.renderArea.extent.width = window.get_width();
		renderInfo.renderArea.extent.height = window.get_heigth();
		
		renderInfo.clearValueCount = 1;
		renderInfo.pClearValues = &clearValues[0];
		renderInfo.pNext = nullptr;

		auto err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
		vkCmdBeginRenderPass(fd->CommandBuffer, &renderInfo, VK_SUBPASS_CONTENTS_INLINE);

		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), fd->CommandBuffer);
	
		vkCmdEndRenderPass(fd->CommandBuffer);
		vkEndCommandBuffer(fd->CommandBuffer);

		
		renderer.inUseCommandBuffers[imguiCommandBufferIndex] = fd->CommandBuffer; 
		

	}

	EMP_FORCEINLINE void refreshImgui(Empaerior::Window& window,VK_Renderer & renderer)
	{
		//std::cout << "1\n\n";
		//vkDeviceWaitIdle(renderer.device);
		if (renderer.framebufferNeedsReconstruction)
		{
			
			vkDeviceWaitIdle(renderer.device);
			
			DettachImgui(window, renderer);
			AttachImgui(window, renderer);
			
		//	ImGui_ImplVulkanH_CreateOrResizeWindow(renderer.instance, renderer.physicalDevice, renderer.device, &wd, renderer.findQueueFamilies(render).graphicsFamily.value(), nullptr, window.get_width(), window.get_heigth(), renderer.swapChainImages.size());
		}
	}

	EMP_FORCEINLINE void Quit(VK_Renderer& renderer)
	{
		ImGuiEmpImpl::Shutdown();
		


		for (size_t i = 0; i < renderer.swapChainImages.size(); i++)
		{
		
			//vkFreeCommandBuffers(renderer.device, Frames[i].CommandPool, 1, nullptr);
			vkDestroyCommandPool(renderer.device, Frames[i].CommandPool, nullptr);


		}
		for (uint32_t i = 0; i < renderer.swapChainImages.size(); i++)
		{
			vkDestroyFramebuffer(renderer.device, Frames[i].Framebuffer, nullptr);
		}

		vkDestroyRenderPass(renderer.device, imguiRenderPass, nullptr);
		ImGui_ImplVulkan_Shutdown();
		ImGui::DestroyContext();


		//remove the coomandBuffer
		//Rendering might not end with ImGUi
		renderer.inUseCommandBuffers.erase(renderer.inUseCommandBuffers.begin() + imguiCommandBufferIndex);

	}

}