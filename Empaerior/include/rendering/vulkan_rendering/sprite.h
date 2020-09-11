#pragma once
#include "geometry_buffer.h"
#include "../include/core/defines/basic_defines.h"
#include "texture_atlas.h"
#include "glyphs.h"
//Rectangle
namespace Empaerior
{
	struct Sprite
	{


		size_t verticesIndex;
		size_t IndicesIndex;
		
		uint32_t texture_id;

		//the size of the allocations in bytes
		size_t verticesSize;
		size_t IndicesSize;

		Empaerior::Float_Rect rect;


		geometryBuffer* parent;
		Texture_Atlas* parent_atlas;

	};


#define EMP_SPR_VERTEX_TOP_LEFT 0
#define EMP_SPR_VERTEX_TOP_RIGHT 3
#define EMP_SPR_VERTEX_BTM_RIGHT 2
#define EMP_SPR_VERTEX_BTM_LEFT 1

	void createSprite(geometryBuffer& buffer, Texture_Atlas& atlas, Sprite& sprite, Empaerior::Float_Rect_S rect, Empaerior::Float_Rect_S tex_rect, uint32_t tex_id);

	void setSpriteRect(Sprite& sprite, geometryBuffer& buffer, Empaerior::Float_Rect_S& rect);

	void setSpritePosition(Sprite& sprite, geometryBuffer& buffer);

	void setSpriteDimensions(Sprite& sprite, Empaerior::fl_point x, Empaerior::fl_point y);

	void setSpriteTexRect (Sprite& sprite, Empaerior::Float_Rect_S rect, Empaerior::u_inter offset = 0);

	void setSpriteDepth(Sprite& sprite, Empaerior::fl_point depth);

	void setSpriteAngle(Sprite& sprite, Empaerior::fl_point angle);

	void setSpriteTexture(Sprite& sprite, Empaerior::u_inter texID);

	Vertex* getSpriteVertex(Sprite& sprite, uint8_t vert);

	





	void createTextSprite(geometryBuffer& buffer, Texture_Atlas& atlas, Sprite& sprite, Empaerior::Float_Rect_S rect, Empaerior::Point2f charDimensions, const Empaerior::Font& font, const char* message, glm::vec3 color);
	

	void setTextSpriteDepth(Sprite& sprite, Empaerior::fl_point depth);
	void setTextSpritePosition(Sprite& sprite, Empaerior::fl_point x, Empaerior::fl_point y);
	void setTextSpriteMessage(Sprite& sprite, Empaerior::Float_Rect_S rect, Empaerior::Point2f charDimensions, const Empaerior::Font& font, const char* message,glm::vec3 color);



	void destroySprite(Sprite& sprite);
}