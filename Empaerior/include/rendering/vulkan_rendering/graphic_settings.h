#pragma once
#include "core/vector2.h"
#include <array>
#include <string>
#include <vulkan/vulkan.h>


namespace Empaerior
{
struct VK_RendererGraphicsInfo
{

    // Shader
    std::string vertShaderpath = "assets/shaders/vert.spv";
    std::string fragShaderpath = "assets/shaders/frag.spv";
    // Viewport
    float viewportX = 0.0f;
    float viewportY = 0.0f;
    float viewportW = 0.0f;
    float viewportH = 0.0f;

    float minDepth = 0.0f;
    float maxDepth = 1.0f;
    // Blending
    bool Blending = VK_FALSE;
    bool LogicOPEnable = VK_FALSE;
    // Depth
    bool Depth = VK_TRUE;
    bool DepthBoundTest = VK_FALSE;
    bool StencilTest = VK_FALSE;
    bool DepthBias = VK_FALSE;
    // rasterizer
    bool DepthClamp = VK_FALSE;
    bool rasterizerDiscardEnable = VK_FALSE;
    float lineWidth = 1.0f;
    // multisampling
    bool sampleShadingEnable = VK_FALSE;

    Empaerior::Vector2<int32_t> scissorOffset = {0, 0};

    float blendConstants[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    std::array<Empaerior::byte, 4> defaultTextureColor = {255, 0, 255, 255};
};
} // namespace Empaerior
