#pragma once
#include "geometry_buffer.h"
#include "core/defines/basic_defines.h"
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

		geometryBuffer* parent;
		Texture_Atlas* parent_atlas;

	};



	void createSprite(geometryBuffer& buffer, Texture_Atlas& atlas, Sprite& sprite, Empaerior::Float_Rect_S rect, Empaerior::Float_Rect_S tex_rect, uint32_t texture_id);

	void setSpriteRect(Sprite& sprite, geometryBuffer& buffer, Empaerior::Float_Rect_S& rect);

	void setSpritePosition(Sprite& sprite, geometryBuffer& buffer);

	void setSpriteDimensions(Sprite& sprite, Empaerior::fl_point x, Empaerior::fl_point y);

	void setSpriteTexRect (Sprite& sprite, Empaerior::Float_Rect_S rect, Empaerior::u_inter offset = 0);

	void setSpriteDepth(Sprite& sprite, Empaerior::fl_point depth);

	void destroySprite(Sprite& sprite);


	void createTextSprite(geometryBuffer& buffer, Texture_Atlas& atlas, Sprite& sprite, Empaerior::Float_Rect_S rect, Empaerior::Point2f charDimensions, const Empaerior::Font& font, const char* message);
	

	void setTextSpriteDepth(Sprite& sprite, Empaerior::fl_point depth);
	void setTextSpritePosition(Sprite& sprite, Empaerior::fl_point x, Empaerior::fl_point y);
	void setTextSpriteMessage(Sprite& sprite, Empaerior::Float_Rect_S rect, Empaerior::Point2f charDimensions, const Empaerior::Font& font, const char* message);

}