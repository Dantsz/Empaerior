

#include <vulkan/vulkan.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../include/rendering/vulkan_rendering/scene.h"
#include "../include/rendering/vulkan_rendering/renderer.h"

void Empaerior::Scene2D::init(VK_Renderer& renderer)
{
    geometrybuffer.attachrenderer(&renderer.allocator,renderer.device,renderer.swapChainImages.size());
}

void Empaerior::Scene2D::updateCamera(const VK_Renderer& renderer,int width,int height)
{
    ubo.scale_mat = glm::mat4(1.0f);
    ubo.scale_mat = glm::scale(glm::mat4(1.0f), glm::vec3((static_cast<float>(width) / renderer.InitialGraphicsSettings.viewportW) * ubo.scaleX, (static_cast<float>(height) / renderer.InitialGraphicsSettings.viewportH) * ubo.scaleY, 0));
    ubo.position_mat = glm::translate(glm::mat4(1.0f), glm::vec3(ubo.position.x * -1, ubo.position.y * -1 , 1.0f));


    ubo.proj = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
}

void Empaerior::Scene2D::cleanup()
{
    geometrybuffer.cleanup();
}