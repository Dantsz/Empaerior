// Everything text
#pragma once
#include "../include/core/defines/defines.h"
#include "../include/debugging/log.h"
#include <ft2build.h>
#include <memory>

#include <iostream>
#include FT_FREETYPE_H

namespace Empaerior
{
namespace FontLoading
{
struct GlyphDimesnsions
{
    Empaerior::fl_point width, height, HbearingY, HbearingX, Mwidth, MHeight; // Mwidh- the actual width of the
                                                                              // character
};
} // namespace FontLoading

struct Font
{

    std::vector<Empaerior::byte> fontTexture;
    std::unique_ptr<char[]> name;
    // the size of each individual glyph
    // glyphSize[i] , i - code of the character
    std::vector<Empaerior::FontLoading::GlyphDimesnsions> glyphSize;
    Empaerior::u_int texWidth, texHeight;

    // the sizes of the whole images
    // its the size of the largest glyph
    FT_Face fontFace;
    Empaerior::fl_point glyphWidth, glyphHeight;
};

namespace FontLoading
{
inline FT_Library fontLibrary;
inline constexpr FT_ULong Characters = 255; // normal ASCII

EMP_FORCEINLINE void initFontEngine()
{
    auto error = FT_Init_FreeType(&Empaerior::FontLoading::fontLibrary);
    if (error != 0)
    {
        // ENGINE_CRITICAL("Failed to initialize the font engine");
    }
}

void createFontFacefrompath(Font &font, const char *path);

EMP_FORCEINLINE void createFontFacefrommemory(Font &font, const Empaerior::byte *buffer, Empaerior::s_inter size)
{
    auto error =
        FT_New_Memory_Face(Empaerior::FontLoading::fontLibrary, buffer, static_cast<FT_Long>(size), 0, &font.fontFace);
    if (error == FT_Err_Unknown_File_Format)
    {
        // ENGINE_ERROR("Font file cannot be read or format is unsupported");
    }
    else if (error != 0)
    {
        // ENGINE_ERROR("File cannot be opened or file is broken");
    }
}

EMP_FORCEINLINE void setFontSize(Font &font, Empaerior::u_int size)
{
    auto error = FT_Set_Pixel_Sizes(font.fontFace, 0, size);
    if (error != 0)
    {
        // ENGINE_ERROR("Failed to set font size ");
    }
}

EMP_FORCEINLINE void createFontTexture(Font &font)
{
    font.fontTexture.clear();
    font.glyphSize.clear();
    Empaerior::u_int width = 0;
    Empaerior::u_int height = 0;
    int pitch = 0;
    // find the max width/height
    for (FT_ULong ch = 0; ch < Characters; ch++)
    {

        if (FT_Load_Char(font.fontFace, ch, FT_LOAD_RENDER) != 0)
        {
            Empaerior::log("ERROR::FREETYTPE: Failed to load Glyph");
        }

        font.glyphSize.push_back({
            static_cast<Empaerior::fl_point>(font.fontFace->glyph->bitmap.width),
            static_cast<Empaerior::fl_point>(font.fontFace->glyph->bitmap.rows),
            static_cast<Empaerior::fl_point>(font.fontFace->glyph->metrics.horiBearingY) / 64,
            static_cast<Empaerior::fl_point>(font.fontFace->glyph->metrics.horiBearingX) / 64,
            static_cast<Empaerior::fl_point>(font.fontFace->glyph->metrics.width) / 64,
            static_cast<Empaerior::fl_point>(font.fontFace->glyph->metrics.height) / 64,
        });

        auto gwidth = font.fontFace->glyph->bitmap.width;
        if (gwidth > width)
        {
            width = gwidth;
        }
        auto gheight = font.fontFace->glyph->bitmap.rows;
        if (gheight > height)
        {
            height = gheight;
        }
        auto gpitch = font.fontFace->glyph->bitmap.pitch;
        if (gpitch > pitch)
        {
            pitch = gpitch;
        }
    }

    font.fontTexture.resize(4 * Characters * width * height);

    font.glyphWidth = static_cast<Empaerior::fl_point>(width);
    font.glyphHeight = static_cast<Empaerior::fl_point>(height);

    font.texWidth = width;

    font.texHeight = Characters * height;
    for (FT_ULong ch = 0; ch < Characters; ch++)
    {

        if (FT_Load_Char(font.fontFace, ch, FT_LOAD_RENDER) != 0)
        {
            Empaerior::log("ERROR::FREETYTPE: Failed to load Glyph");
        }

        Empaerior::u_inter cwidth = font.fontFace->glyph->bitmap.width;
        Empaerior::u_inter cheight = font.fontFace->glyph->bitmap.rows;

        uint8_t *src = font.fontFace->glyph->bitmap.buffer;
        uint8_t *startOfLine = src;

        Empaerior::u_inter dst = 4 * static_cast<Empaerior::u_inter>(ch) * height * width;

        for (Empaerior::u_inter y = 0; y < cheight; ++y)
        {
            src = startOfLine;
            for (Empaerior::u_inter x = 0; x < cwidth; ++x)
            {

                auto value = *src;
                src++;
                if (value != 0xff)
                {
                    value = 0;
                }
                font.fontTexture[dst++] = 0x0;
                font.fontTexture[dst++] = 0x0;
                font.fontTexture[dst++] = 0x0;
                font.fontTexture[dst++] = value;
            }
            for (Empaerior::u_inter x = cwidth; x < width; ++x)
            {
                font.fontTexture[dst++] = 0x0;
                font.fontTexture[dst++] = 0x0;
                font.fontTexture[dst++] = 0x0;
                font.fontTexture[dst++] = 0;
            }

            startOfLine += font.fontFace->glyph->bitmap.pitch;
        }
    }
}
} // namespace FontLoading

} // namespace Empaerior
