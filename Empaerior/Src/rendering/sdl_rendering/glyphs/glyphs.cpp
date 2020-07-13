#include "pch.h"
#include "glyphs.h"
#include "../../../assetmanager/assetmanager.h"
#include "rendering/sdl_rendering/sdl_renderer.h"
#include "application.h"
namespace Empaerior {



	Empaerior::byte createGlyphs(Empaerior::vector<surface_glyph>& s_glyphs ,const Empaerior::string& path,const Empaerior::u_int& size, Empaerior::Color& color)
	{
	
		Empaerior::ch fontChar[EMP_LETTERS] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,!@#$%&:;'{}[]<>/+-=*";
		fontChar[84] = '"'; fontChar[EMP_LETTERS - 1] = ' ';
		SDL_Surface* tempSurface;
		TTF_Font* font = Empaerior::Asset_Loading::load_font(path, size);
		if (font == nullptr)  return -1;
		surface_glyph temp;
		Empaerior::ch shortString[2] = "";

		for (int cnt = 0; cnt < EMP_LETTERS; cnt++) {

			shortString[0] = fontChar[cnt];
			tempSurface = TTF_RenderText_Solid(font, shortString, color);
			temp.surface = tempSurface;
			s_glyphs.push_back(std::move(temp));
		}
		return 1;
	}


	





	void Create_text_texture(const Empaerior::vector<Empaerior::byte>& text, const Empaerior::Float_Rect& rect , std::vector<surface_glyph>& s_glyphs, SDL_Renderer* renderer,std::shared_ptr<SDL_Texture>& texture,Empaerior::Int_Rect& tex_rect)
	{
		Empaerior::fl_point x = 0, y = 0, wX = 0;
		Empaerior::Float_Rect_S textRect;
		Empaerior::byte lValue = 0;
		Empaerior::u_inter lastSpace = 0;
		Empaerior::boole safe = true;
	
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
#endif

		SDL_Surface* blitting_texture = SDL_CreateRGBSurface(0, static_cast<int>(rect.dimensions.w), static_cast<int>(rect.dimensions.h), 32,
			rmask, gmask, bmask, amask);
		
		for (Empaerior::u_inter cnt = 0; cnt < text.size(); cnt++)
		{   //covert from character to glyph id
			lValue = text[cnt];
			
			if (lValue == 85) {
				lastSpace = cnt; wX = x + s_glyphs[85].surface->w;
				//need to read ahead make sure room for next word if not then skip to next line
				for (Empaerior::u_inter t = lastSpace + 1; t < text.size(); t++) {
					int m_lValue = text[t];
					wX = wX + s_glyphs[m_lValue].surface->w;
					if (wX >= rect.dimensions.w) {
						safe = false;
						break;
					}
					if (m_lValue == 85) {
						safe = true;
						break;
					}
				}
			}
			if (safe) {

		
				textRect.x = x; textRect.y = y; textRect.w = static_cast<Empaerior::fl_point>(s_glyphs[lValue].surface->w); textRect.h = static_cast<Empaerior::fl_point>(s_glyphs[lValue].surface->h);
				
				SDL_Rect i_dstrect = { static_cast<int>(textRect.x) , static_cast<int>(textRect.y)  , static_cast<int>(textRect.w) , static_cast<int>(textRect.h) };
			
				
				SDL_BlitSurface(s_glyphs[lValue].surface , NULL, blitting_texture, &i_dstrect);

				x = x + s_glyphs[lValue].surface->w;
			}
			else { cnt = lastSpace; x = 0; y = y + s_glyphs[lValue].surface->h; safe = true; }
		}
		tex_rect.x = 0;
		tex_rect.y = 0;
		tex_rect.w = blitting_texture->w;
		tex_rect.h = blitting_texture->h;
		texture = sdl_shared<SDL_Texture>(SDL_CreateTextureFromSurface(Empaerior::SDL_Rendering::get_renderer(), blitting_texture));
	

		SDL_FreeSurface(blitting_texture);
	
	}

	Empaerior::vector<Empaerior::byte> load_glyph_values(const Empaerior::string& source)
	{
	
		Empaerior::vector<Empaerior::byte> text;
		for (int i = 0; i < source.length(); i++) {
			text.emplace_back(getValue(source[i]));
		}

		return text;
	}




	int getValue(Empaerior::ch Letter) {

		switch (Letter) {
		case '0':
		{
			return 0;
		}
		case '1':
		{
			return 1;
		}
		case '2':
		{
			return 2;
		}
		case '3':
		{
			return 3;
		}
		case '4':
		{
			return 4;
		}
		case '5':
		{
			return 5;
		}
		case '6':
		{
			return 6;
		}
		case '7':
		{
			return 7;
		}
		case '8':
		{
			return 8;
		}
		case '9':
		{
			return 9;
		}
		case 'a':
		{
			return 10;
		}
		case 'b':
		{
			return 11;
		}
		case 'c':
		{
			return 12;
		}
		case 'd':
		{
			return 13;
		}
		case 'e':
		{
			return 14;
		}
		case 'f':
		{
			return 15;
		}
		case 'g':
		{
			return 16;
		}
		case 'h':
		{
			return 17;
		}
		case 'i':
		{
			return 18;
		}
		case 'j':
		{
			return 19;
		}
		case 'k':
		{
			return 20;
		}
		case 'l':
		{
			return 21;
		}
		case 'm':
		{
			return 22;
		}
		case 'n':
		{
			return 23;
		}
		case 'o':
		{
			return 24;
		}
		case 'p':
		{
			return 25;
		}
		case 'q':
		{
			return 26;
		}
		case 'r':
		{
			return 27;
		}
		case 's':
		{
			return 28;
		}
		case 't':
		{
			return 29;
		}
		case 'u':
		{
			return 30;
		}
		case 'v':
		{
			return 31;
		}
		case 'w':
		{
			return 32;
		}
		case 'x':
		{
			return 33;
		}
		case 'y':
		{
			return 34;
		}
		case 'z':
		{
			return 35;
		}
		case 'A':
		{
			return 36;
		}
		case 'B':
		{
			return 37;
		}
		case 'C':
		{
			return 38;
		}
		case 'D':
		{
			return 39;
		}
		case 'E':
		{
			return 40;
		}
		case 'F':
		{
			return 41;
		}
		case 'G':
		{
			return 42;
		}
		case 'H':
		{
			return 43;
		}
		case 'I':
		{
			return 44;
		}
		case 'J':
		{
			return 45;
		}
		case 'K':
		{
			return 46;
		}
		case 'L':
		{
			return 47;
		}
		case 'M':
		{
			return 48;
		}
		case 'N':
		{
			return 49;
		}
		case 'O':
		{
			return 50;
		}
		case 'P':
		{
			return 51;
		}
		case 'Q':
		{
			return 52;
		}
		case 'R':
		{
			return 53;
		}
		case 'S':
		{
			return 54;
		}
		case 'T':
		{
			return 55;
		}
		case 'U':
		{
			return 56;
		}
		case 'V':
		{
			return 57;
		}
		case 'W':
		{
			return 58;
		}
		case 'X':
		{
			return 59;
		}
		case 'Y':
		{
			return 60;
		}
		case 'Z':
		{
			return 61;
		}
		case '.':
		{
			return 62;
		}
		case ',':
		{
			return 63;
		}
		case '!':
		{
			return 64;
		}
		case '@':
		{
			return 65;
		}
		case '#':
		{
			return 66;
		}
		case '$':
		{
			return 67;
		}
		case '%':
		{
			return 68;
		}
		case '&':
		{
			return 69;
		}
		case ':':
		{
			return 70;
		}
		case ';':
		{
			return 71;
		}
		case '\'':
		{
			return 72;
		}
		case '{':
		{
			return 73;
		}
		case '}':
		{
			return 74;
		}
		case '[':
		{
			return 75;
		}
		case ']':
		{
			return 76;
		}
		case '<':
		{
			return 77;
		}
		case '>':
		{
			return 78;
		}
		case '/':
		{
			return 79;
		}
		case '+':
		{
			return 80;
		}
		case '-':
		{
			return 81;
		}
		case '=':
		{
			return 82;
		}
		case '*':
		{
			return 83;
		}
		case '"':
		{
			return 84;
		}
		case ' ':
		{
			return 85;
		}
		case '\r':
		{
			return 85;
		}
		case '\n':
		{
			return 85;
		}
		case '\t':
		{
			return 85;
		}
		default:
		{
			return 85;
		}

		break;
		}
		return 85;
	}

}