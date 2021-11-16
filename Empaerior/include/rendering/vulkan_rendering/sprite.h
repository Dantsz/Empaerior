#pragma once
#include "../include/core/defines/basic_defines.h"
#include "geometry_buffer.h"
#include "glyphs.h"
#include "scene.h"
#include "texture_atlas.h"

class VK_Renderer;
namespace Empaerior
{
struct Sprite
{

    // the number of vertices and indices a sprite needs
    static constexpr size_t nIndices = 6;
    static constexpr size_t nVertices = 4;

    size_t verticesIndex;
    size_t indicesIndex;

    // the size of the allocations in bytes
    size_t verticesSize;
    size_t indicesSize;

    Empaerior::Float_Rect rect;
    uint32_t texture_id;

    geometryBuffer *parent;
    Texture_Atlas *parent_atlas;
};

enum spriteCorners
{
    sprTopLeft = 0,
    sprBottomLeft = 1,
    sprBottomRight = 2,
    sprTopRight = 3,
};

// takes geometrybuffer and atlas
void createSprite(geometryBuffer &buffer, Texture_Atlas &atlas, Sprite &sprite, Empaerior::Float_Rect_S rect,
                  Empaerior::Float_Rect_S tex_rect, uint32_t tex_id);
// takes the renderer
// uses the buffer from the default scene
void createSprite(VK_Renderer &renderer, Sprite &sprite, Empaerior::Float_Rect_S rect, Empaerior::Float_Rect_S tex_rect,
                  uint32_t tex_id);
// takes the renderer and scene
void createSprite(VK_Renderer &renderer, Empaerior::Scene2D &scene, Sprite &sprite, Empaerior::Float_Rect_S rect,
                  Empaerior::Float_Rect_S tex_rect, uint32_t tex_id);

void setSpriteRect(Sprite &sprite, Empaerior::Float_Rect_S &rect);

void setSpritePosition(Sprite &sprite, geometryBuffer &buffer);

void setSpriteDimensions(Sprite &sprite, Empaerior::fl_point width, Empaerior::fl_point height);

void setSpriteTexRect(Sprite &sprite, Empaerior::Float_Rect_S rect, Empaerior::u_inter offset = 0);

void setSpriteDepth(Sprite &sprite, Empaerior::fl_point depth);

void setSpriteAngle(Sprite &sprite, Empaerior::fl_point angle);

void setSpriteTexture(Sprite &sprite, Empaerior::u_int texID);

Vertex *getSpriteVertex(Sprite &sprite, uint8_t vert);

// geombuffer and atlas
void createTextSprite(geometryBuffer &buffer, Texture_Atlas &atlas, Sprite &sprite, Empaerior::Float_Rect_S rect,
                      Empaerior::Point2f charDimensions, const Empaerior::Font &font, const char *message,
                      glm::vec3 color);
// renderer
void createTextSprite(VK_Renderer &renderer, Sprite &sprite, Empaerior::Float_Rect_S rect,
                      Empaerior::Point2f charDimensions, const Empaerior::Font &font, const char *message,
                      glm::vec3 color);
// renderer and scene
void createTextSprite(VK_Renderer &renderer, Empaerior::Scene2D &scene, Sprite &sprite, Empaerior::Float_Rect_S rect,
                      Empaerior::Point2f charDimensions, const Empaerior::Font &font, const char *message,
                      glm::vec3 color);

void setTextSpriteDepth(Sprite &sprite, Empaerior::fl_point depth);
void setTextSpritePosition(Sprite &sprite, Empaerior::fl_point x, Empaerior::fl_point y);
void setTextSpriteMessage(Sprite &sprite, Empaerior::Float_Rect_S rect, Empaerior::Point2f charDimensions,
                          const Empaerior::Font &font, const char *message, glm::vec3 color);

void destroySprite(Sprite &sprite);

// functions with VK_Renderer as parameter

} // namespace Empaerior
