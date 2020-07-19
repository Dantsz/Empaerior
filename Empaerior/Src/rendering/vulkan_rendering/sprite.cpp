
#include "sprite.h"
#include "glyphs.h"
namespace Empaerior
{
	void createSprite(geometryBuffer& buffer, Texture_Atlas& atlas, Sprite& sprite, Empaerior::Float_Rect_S rect, Empaerior::Float_Rect_S tex_rect, uint32_t tex_id)
	{

		sprite.parent = &buffer;
		sprite.parent_atlas = &atlas;

		sprite.IndicesIndex = buffer.indexBuffer.allocate(6 * sizeof(uint32_t));
		sprite.verticesIndex = buffer.vertexBuffer.allocate(4 * sizeof(Vertex));
		sprite.IndicesSize = 6 * sizeof(uint32_t);
		sprite.verticesSize = 4 * sizeof(Vertex);

		sprite.texture_id = tex_id;


		*((Vertex*)buffer.vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex)) = { {  rect.x,rect.y ,0.0f},                      { 0.0f,0.0f } ,tex_id , {0.0f,0.0f,0.0f} };
		*((Vertex*)buffer.vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 1) = { {rect.x, rect.y + rect.h,0.0f },          {0.0f,1.0f}, tex_id, {0.0f,0.0f,0.0f} };
		*((Vertex*)buffer.vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 2) = { { rect.x + rect.w, rect.y + rect.h,0.0f}, {0.14f,1.0f},tex_id, {0.0f,0.0f,0.0f} };
		*((Vertex*)buffer.vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 3) = { { rect.x + rect.w,rect.y ,0.0f},          {0.14f,0.0f},tex_id , {0.0f,0.0f,0.0f} };

		*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t)) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex);
		*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + 1) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 1;
		*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + 2) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 2;

		*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + 3) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 2;
		*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + 4) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 3;
		*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + 5) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex);

		setSpriteTexRect(sprite, tex_rect);
	}

	void createTextSprite(geometryBuffer& buffer, Texture_Atlas& atlas, Sprite& sprite,Empaerior::Float_Rect_S rect, Empaerior::Point2f charDimensions , const Empaerior::Font &  font, const char* message)
	{
		if (strlen(message) == 0) return;

		sprite.parent = &buffer;
		sprite.parent_atlas = &atlas;

		sprite.IndicesIndex = buffer.indexBuffer.allocate(strlen(message) * 6 * sizeof(uint32_t));
		sprite.verticesIndex = buffer.vertexBuffer.allocate(strlen(message) * 4 * sizeof(Vertex));

		sprite.IndicesSize = strlen(message) * 6 * sizeof(uint32_t);
		sprite.verticesSize = strlen(message) *  4 * sizeof(Vertex);

		sprite.texture_id = atlas.getFont(font.name);
	

		Empaerior::fl_point beginX = rect.x;
		Empaerior::fl_point beginY = rect.y;

		for (size_t i = 0; i < strlen(message); i++)
		{
			//used to transform the width and height based on the char size
			Empaerior::fl_point ar;
			if (font.glyphSize[message[i]].height > 0.0001) ar = font.glyphSize[message[i]].width / font.glyphSize[message[i]].height;
			else  ar = 1.0f;

			//calculate if the character fits and how much it fits
			Empaerior::fl_point CharWidth;
			if (beginX + charDimensions.elements[0] * ar >= rect.w + rect.x) {
				//CharWidth = charDimensions.elements[0] * ar - beginX - charDimensions.elements[0] * ar + rect.w + rect.x;
				beginY += charDimensions[1];
				beginX = rect.x;
			}

			if (beginY >= rect.y + rect.h) return;

			CharWidth = charDimensions.elements[0] * ar;

		

			//set data
			*((Vertex*)buffer.vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + i *4)       = { { beginX,                                  beginY                               ,        0.0f},                        {0.0f,0.0f} , sprite.texture_id, {0.0f,0.0f,0.0f} };
			*((Vertex*)buffer.vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 1 + i * 4 ) = { { beginX,                                  beginY + charDimensions.elements[1]  ,        0.0f},                            {0.0f,1.0f},  sprite.texture_id, {0.0f,0.0f,0.0f} };
			*((Vertex*)buffer.vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 2 + i * 4)  = { { beginX + CharWidth ,                     beginY  + charDimensions.elements[1] ,        0.0f},                           {0.14f,1.0f}, sprite.texture_id , {0.0f,0.0f,0.0f} };
			*((Vertex*)buffer.vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 3 + i * 4)  = { { beginX + CharWidth,                      beginY                               ,        0.0f},                                                    {0.14f,0.0f}, sprite.texture_id , {0.0f,0.0f,0.0f} };
		
			*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + i * 6)  = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + i * 4;
			*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + 1 + i * 6) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 1 + i * 4;
			*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + 2 + i * 6) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 2 + i * 4;

			*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + 3 + i * 6) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 2 + i * 4;
			*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + 4 + i * 6) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 3 + i * 4;
			*((uint32_t*)buffer.indexBuffer.BuffersData[buffer.indexBuffer.get_in_use_index()] + buffer.indexBuffer.index[sprite.IndicesIndex] / sizeof(uint32_t) + 5 + i * 6) = buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + i * 4;

			//set texture cropping (how much of a letter is visible)
			Empaerior::fl_point  visibilityX = CharWidth /  (charDimensions.elements[0] * ar);
			//check if the whole letter is present
			Empaerior::fl_point visibilityY;
			if (beginY + charDimensions.elements[1] > rect.y + rect.h) visibilityY = (rect.y + rect.h) / (beginY + charDimensions.elements[1]);
			else visibilityY = 1.0f;


			setSpriteTexRect(sprite, { 0, message[i] * font.glyphHeight   , font.glyphSize[message[i]].width  * visibilityX,font.glyphSize[message[i]].height  * visibilityY} , i *  4 );
			beginX += charDimensions.elements[0] ;


			
		}
	



	}



	void setSpriteRect(Sprite& sprite, geometryBuffer& buffer, Empaerior::Float_Rect_S& rect)
	{
		((Vertex*)sprite.parent->vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex))->pos = { rect.x,rect.y,0.0f };

		((Vertex*)sprite.parent->vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 1)->pos = { rect.x , rect.y + rect.h ,0.0f };

		((Vertex*)sprite.parent->vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 2)->pos = { rect.x + rect.w, rect.y + rect.h,0.0f };

		((Vertex*)sprite.parent->vertexBuffer.BuffersData[buffer.vertexBuffer.get_in_use_index()] + buffer.vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + 3)->pos = { rect.x + rect.w, rect.y ,0.0f };

	}

	void setSpriteDimensions(Sprite& sprite, Empaerior::fl_point x, Empaerior::fl_point y)
	{
#define vertex ((Vertex*)sprite.parent->vertexBuffer.BuffersData[sprite.parent->vertexBuffer.get_in_use_index()] + sprite.parent->vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex))
		(vertex + 1)->pos.y = vertex->pos.y + y;
		(vertex + 2)->pos = { vertex->pos.x + x, vertex->pos.y + y,0.0f };
		(vertex + 3)->pos.x = vertex->pos.x + x;
#undef vertex
	}

	void setSpriteTexRect(Sprite& sprite, Empaerior::Float_Rect_S rect , Empaerior::u_inter offset  )
	{
		rect.x /= sprite.parent_atlas->image_dimensions[sprite.texture_id].elements[0];
		rect.w /= sprite.parent_atlas->image_dimensions[sprite.texture_id].elements[0];
		rect.y /= sprite.parent_atlas->image_dimensions[sprite.texture_id].elements[1];
		rect.h /= sprite.parent_atlas->image_dimensions[sprite.texture_id].elements[1];

		((Vertex*)sprite.parent->vertexBuffer.BuffersData[sprite.parent->vertexBuffer.get_in_use_index()] + sprite.parent->vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + offset)->texCoord = { rect.x,rect.y };
		((Vertex*)sprite.parent->vertexBuffer.BuffersData[sprite.parent->vertexBuffer.get_in_use_index()] + sprite.parent->vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + offset + 1)->texCoord = { rect.x , rect.y + rect.h };
		((Vertex*)sprite.parent->vertexBuffer.BuffersData[sprite.parent->vertexBuffer.get_in_use_index()] + sprite.parent->vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + offset +  2)->texCoord = { rect.x + rect.w, rect.y + rect.h };
		((Vertex*)sprite.parent->vertexBuffer.BuffersData[sprite.parent->vertexBuffer.get_in_use_index()] + sprite.parent->vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex) + offset +  3)->texCoord = { rect.x + rect.w, rect.y };

	}

	void setSpriteDepth(Sprite& sprite, Empaerior::fl_point depth)
	{
#define vertex ((Vertex*)sprite.parent->vertexBuffer.BuffersData[sprite.parent->vertexBuffer.get_in_use_index()] + sprite.parent->vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex))
		vertex->pos.z = depth;
		(vertex + 1)->pos.z = depth;
		(vertex + 2)->pos.z = depth;
		(vertex + 3)->pos.z = depth;
#undef vertex
	}

	void setTextSpriteDepth(Sprite& sprite, Empaerior::fl_point depth)
	{
#define vertex ((Vertex*)sprite.parent->vertexBuffer.BuffersData[sprite.parent->vertexBuffer.get_in_use_index()] + sprite.parent->vertexBuffer.index[sprite.verticesIndex] / sizeof(Vertex))
		for (size_t i = 0; i < sprite.verticesSize / ( sizeof(Vertex)); i++)
		{
			(vertex + i)->pos.z = depth;
		}

#undef vertex

	}




	//deletes sprite from buffer 
	//the data is erased from the buffer
	//costly 
	void destroySprite(Sprite& sprite)
	{




		uint32_t* data = (uint32_t*)sprite.parent->indexBuffer.BuffersData[sprite.parent->indexBuffer.get_in_use_index()];


		//the vertex data moved , so the index buffer needs to be adjusted
		for (size_t i = sprite.parent->indexBuffer.index[sprite.IndicesIndex]; i < sprite.parent->indexBuffer.used_size[sprite.parent->indexBuffer.get_in_use_index()]; i++)
		{
			data[i] -= (sprite.verticesSize / sizeof(Vertex));
		}

		sprite.parent->indexBuffer.deallocate(sprite.IndicesIndex, sprite.IndicesSize);

		sprite.parent->vertexBuffer.deallocate(sprite.verticesIndex, sprite.verticesSize);


	}

	
}
