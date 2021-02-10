#include "..\..\..\include\rendering\vulkan_rendering\glyphs.h"

static void stringCopy(char* dst, const char* src, size_t numberofCharstoCopy  )
{
    if(strlen(src) < numberofCharstoCopy) return;
    for(int i = 0 ; i < numberofCharstoCopy ; i ++) dst[i] = src[i];

}


namespace Empaerior
{
    void FontLoading::createFontFacefrompath(Font& font, const char* path)
            {
                auto error = FT_New_Face(Empaerior::FontLoading::fontLibrary, path, 0, &font.fontFace);
                if (error == FT_Err_Unknown_File_Format)
                {
                    ENGINE_ERROR("Font file cannot be read or format is unsupported");
                }
                else if (error)
                {
                    ENGINE_ERROR("File cannot be opened or file is broken");
                }

                font.name = std::make_unique<char[]>(strlen(path)+ 1);
                //do alternative here pls
               
                stringCopy(font.name.get(),path,strlen(path));
            }
}