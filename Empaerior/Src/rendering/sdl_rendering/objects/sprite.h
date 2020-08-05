#pragma once
#include "../Include/core/exceptions/exceptions.h"
#include "../Include/assetmanager/assetmanager.h"
#include "../../camera.h"
#include "rendering/sdl_rendering/sdl_renderer.h"


namespace Empaerior {
	///base  class for sprite elements, practically vritual
	class Graphic_element
	{
	public:

	

		~Graphic_element()
		{

		}
	
	
	


		void set_position(const Empaerior::fl_point x, const Empaerior::fl_point y)
		{
			rect.dimensions.x = x;
			rect.dimensions.y = y;
			return;
		}


		// the size of the rect is only for one frame of the sprite
	// so the length of the texture should be frames * tex_rect.w
	
		//sets a new texture instead of the old one
		//rect , animation  and position doesn't change
		void set_texture(const Empaerior::string& tex_path)
		{
			texture = Asset_Loading::load_texture_from_file(tex_path);
	
		}

		void set_texture(const std::shared_ptr<SDL_Texture>& tex)
		{
			texture = tex;
			
		}
		//changes the color of the texture to the rgb value provided
		//255,255,255 - 
		void set_color_blend(Empaerior::byte p_r, Empaerior::byte p_g, Empaerior::byte p_b)
		{
			r = p_r;
			g = p_g;
			b = p_b;
		}
	

		//sets the interval between frame updates of the animation
		//in milliseconds
		void set_hold_time(const Empaerior::u_int new_holdTime)
		{
			try {
				//setting new_frames to 0 should logacally result in an infinite loop 
				//as the animation is constantly being updated with no time in between updates
				if (new_holdTime == 0) throw E_runtime_exception("Hold time cannot be zero", __FILE__, __LINE__, __FUNCTION__);
				holdTime = new_holdTime;
			}
			catch (E_runtime_exception& e)
			{
				e.print_message();
				return;
			}
		}

		//gets the dimesnions of the sprite
		Empaerior::Float_Rect& get_rect() { return rect; }
		
		

	
	
	public:
		std::shared_ptr<SDL_Texture> texture;
		//it's the tecture path for sprites and font_path dor text_sprites;


	
		
		Empaerior::u_inter animation_begin;//the very first frame of the animation
		Empaerior::u_inter cur_frame;//the id of the current animation
		Empaerior::u_inter animation_end;//the last non-repeating frame of the animation

		Empaerior::Int_Rect tex_rect;// the portion of the texture the sprite represents


		//the initial animation the entity had when emplace_sprite/emplace_text_sprite was called
		//it can be deleted
		Empaerior::u_inter default_anim_frame;//
		
		Empaerior::u_int time = 0;
		Empaerior::u_int holdTime = 250; //time between animations currently 0.25 seconds

		

		//color values
		Empaerior::byte r = 255;
		Empaerior::byte g = 255;
		Empaerior::byte b = 255;

		Empaerior::Float_Rect rect; // the sprite

		//used to calculate the position relative to the camera
		//Empaerior::Float_Rect_S position_rect;

	};

	

	namespace SpriteFunctions
	{
		EMP_FORCEINLINE void set_angle(Empaerior::Graphic_element& spr,const Empaerior::fl_point& newAngle)
		{
			spr.rect.angle = newAngle;
		}

		EMP_FORCEINLINE void set_position(Empaerior::Graphic_element& spr,const Empaerior::fl_point& x, const Empaerior::fl_point& y)
		{
			spr.rect.dimensions.x = x;
			spr.rect.dimensions.y = y;
			return;
		}
		EMP_FORCEINLINE void set_position(Empaerior::Graphic_element& spr,const Empaerior::Point2f& point)
		{
			spr.rect.dimensions.x = point[0];
			spr.rect.dimensions.y = point[1];
			return;
		}
		//Initialize as a normal sprite 
		EMP_FORCEINLINE void InitSprite(Empaerior::Graphic_element& spr,const Empaerior::Float_Rect& m_rect, const Empaerior::string& tex_path)
		{
		
			spr.rect = m_rect;
		
			// load the texture
			spr.texture = Asset_Loading::load_texture_from_file(tex_path);
			
		}

		//Initialize as a Text_Sprite
		void InitTextSprite(Empaerior::Graphic_element& spr, const Empaerior::Float_Rect& rect, const Empaerior::string& font_path, const  Empaerior::u_int& size, const Empaerior::string& message, Empaerior::Color& color);
	
		//SETS THE MESSAGE
		void set_message(Empaerior::Graphic_element& spr, const Empaerior::string& font_path , const Empaerior::string& message, const Empaerior::s_int& size);
		
		//Completely resets every component of the sprite
		EMP_FORCEINLINE void resetSPR(Empaerior::Graphic_element& spr)
		{
			spr.texture.reset();
			spr.tex_rect = {};
			
			spr.time = 0;
			spr.holdTime = 250;
		
			spr.cur_frame = 0;
			spr.r = 255;
			spr.g = 255;
			spr.b = 255;
			spr.rect = { {0,0,0,0},0 };
			
		}

		
	}



}

