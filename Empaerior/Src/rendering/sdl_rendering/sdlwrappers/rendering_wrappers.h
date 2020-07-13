#pragma once
//Wrappes library functions
#include <SDL.h>
#include "core/defines/defines.h"



namespace Empaerior
{

	using Int_Rect = SDL_Rect;

	using Color = SDL_Color;

	namespace Render
	{

		//TODO: USe SDL_RenderCopyFEx instead of SDL_RenderCopyEx
			EMP_FORCEINLINE void RenderEx(SDL_Renderer* renderer,
			SDL_Texture* texture,
			const SDL_RendererFlip flip,
			const double& angle,
			const SDL_Point* center,
			const Empaerior::Int_Rect* srcrect,	
			const Empaerior::Float_Rect_S* dstrect = nullptr)
		{
		
				SDL_Rect i_dstrect = { static_cast<int>(dstrect->x) , static_cast<int>(dstrect->y)  , static_cast<int>(dstrect->w) , static_cast<int>(dstrect->h) };
				SDL_Rect* pdsrect = &i_dstrect;
				SDL_RenderCopyEx(renderer, texture, srcrect, pdsrect, angle, center, flip);
			
		
		}


	}

}