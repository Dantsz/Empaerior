#include "pch.h"
#include "sprite.h"
#include "application.h"
#include "rendering/sdl_rendering/sdl_renderer.h"
#include "../../window.h"




void Empaerior::SpriteFunctions::InitTextSprite(Empaerior::Graphic_element& spr, const Empaerior::Float_Rect& rect , const Empaerior::string& font_path, const Empaerior::u_int& size, const Empaerior::string& message, Empaerior::Color& color)
{
	spr.rect = rect;
	spr.r = color.r;
	spr.g = color.g;
	spr.b = color.b;
	
	Create_text_texture(load_glyph_values(message), rect, *Empaerior::Asset_Loading::load_glyph_vector(font_path, size), Empaerior::SDL_Rendering::get_renderer(), spr.texture, spr.tex_rect);
}

void Empaerior::SpriteFunctions::set_message(Empaerior::Graphic_element& spr,const Empaerior::string& font_path ,const Empaerior::string& message, const Empaerior::s_int& size)
{
	Create_text_texture(load_glyph_values(message), spr.rect, *Empaerior::Asset_Loading::load_glyph_vector(font_path, size), Empaerior::SDL_Rendering::get_renderer(), spr.texture,spr.tex_rect);
}
