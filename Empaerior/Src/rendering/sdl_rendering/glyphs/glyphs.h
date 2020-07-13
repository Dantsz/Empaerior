#pragma once
//thanks to GRHmedia  for his glyphs system




#include "rendering/sdl_rendering/sdlwrappers/ptr_wrappers.h"
#include "rendering/sdl_rendering/sdlwrappers/rendering_wrappers.h"
namespace Empaerior {



	enum class LETTERS {
		a = 10, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, PERIOD, COMMA,
		EXCLAMATION, AT, HASH, DOLLAR_SIGN, PERCENT, AND, COLON, S_SOLON, SINGLE_QUOTE, DOUBLE_QUOTE, LEFT_BRACKET, RIGHT_BRACKET, LEFT_SQUARE,
		RIGHT_SQUARE, LESS_THAN, GREATER_THAN, DIVIDE, PLUS, MINUS, EQUAL, MULTIPLY, SPACE, RETURN, NEW_LINE, TAB
	};
	#define EMP_LETTERS 86

	//glyphs must be deallocated 


	class surface_glyph{
	public:
		void clean()
		{
			if (surface == nullptr) SDL_FreeSurface(surface);
		}

		SDL_Surface* surface;
		
	};



	//This function uses an array instead of a vector
	Empaerior::byte createGlyphs(Empaerior::vector<surface_glyph>& s_glyphs , const Empaerior::string& path, const  Empaerior::u_int& size, Empaerior::Color& color);


	void Create_text_texture(const Empaerior::vector<Empaerior::byte>& text, const Empaerior::Float_Rect& rect, Empaerior::vector<surface_glyph>& s_glyphs, SDL_Renderer* renderer, std::shared_ptr<SDL_Texture>& texture, Empaerior::Int_Rect& tex_rect);


	Empaerior::vector<Empaerior::byte> load_glyph_values(const  Empaerior::string& source);
	int getValue(Empaerior::ch Letter);





}