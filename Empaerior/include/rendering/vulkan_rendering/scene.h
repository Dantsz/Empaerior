#pragma once

#include "geometry_buffer.h"
#include "camera.h"
class VK_Renderer;

namespace Empaerior
{

class Scene2D
{
    public:


    void init(VK_Renderer& renderer);
    void updateCamera(const VK_Renderer& renderer,int width,int height);
    void cleanup();
    
    Empaerior::Camera2D ubo{};
    geometryBuffer geometrybuffer;
    private:
    
    


};
}
