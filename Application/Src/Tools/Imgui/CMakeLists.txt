
set(Imgui
    "Src/Tools/Imgui/Emp_Imgui.h"
)
source_group("Tools\\Imgui" FILES ${Imgui})

set(Imgui__imgui-empaerior
    "Src/Tools/Imgui/imgui-empaerior/imgui_empaerior.cpp"
    "Src/Tools/Imgui/imgui-empaerior/imgui_empaerior.h"
    "Src/Tools/Imgui/imgui-empaerior/imgui_impl_vulkan.h"
    "Src/Tools/Imgui/imgui-empaerior/imgui_impl_vulkan.cpp"
)
source_group("Tools\\Imgui\\imgui-empaerior" FILES ${Imgui__imgui-empaerior})

set(Imgui__imgui-master
    "Src/Tools/Imgui/imgui-master/imconfig.h"
    "Src/Tools/Imgui/imgui-master/imgui.cpp"
    "Src/Tools/Imgui/imgui-master/imgui.h"
    "Src/Tools/Imgui/imgui-master/imgui_demo.cpp"
    "Src/Tools/Imgui/imgui-master/imgui_draw.cpp"
    "Src/Tools/Imgui/imgui-master/imgui_internal.h"
    "Src/Tools/Imgui/imgui-master/imgui_widgets.cpp"
    "Src/Tools/Imgui/imgui-master/imstb_rectpack.h"
    "Src/Tools/Imgui/imgui-master/imstb_textedit.h"
    "Src/Tools/Imgui/imgui-master/imstb_truetype.h"
)
source_group("Tools\\Imgui\\imgui-master" FILES ${Imgui__imgui-master})

set(Imgui__imgui-master__misc__cpp
    "Src/Tools/Imgui/imgui-master/misc/cpp/imgui_stdlib.cpp"
    "Src/Tools/Imgui/imgui-master/misc/cpp/imgui_stdlib.h"
)
source_group("Tools\\Imgui\\imgui-master\\misc\\cpp" FILES ${Imgui__imgui-master__misc__cpp})

set(Imgui__imgui-master__misc__fonts
    "Src/Tools/Imgui/imgui-master/misc/fonts/binary_to_compressed_c.cpp"
)
source_group("Tools\\Imgui\\imgui-master\\misc\\fonts" FILES ${Imgui__imgui-master__misc__fonts})

set(Imgui__imgui-master__misc__single_file
    "Src/Tools/Imgui/imgui-master/misc/single_file/imgui_single_file.h"
)
source_group("Tools\\Imgui\\imgui-master\\misc\\single_file" FILES ${Imgui__imgui-master__misc__single_file})

set(Imgui__imgui_sdl-master
    "Src/Tools/Imgui/imgui_sdl-master/example.cpp"
    "Src/Tools/Imgui/imgui_sdl-master/imgui_sdl.cpp"
    "Src/Tools/Imgui/imgui_sdl-master/imgui_sdl.h"
)
source_group("Tools\\Imgui\\imgui_sdl-master" FILES ${Imgui__imgui_sdl-master})

#Add the files
set(ALL_FILES
    ${ALL_FILES}
	
    ${Imgui}
    ${Imgui__imgui-empaerior}
    ${Imgui__imgui-master}
    ${Imgui__imgui-master__misc__cpp}
    ${Imgui__imgui-master__misc__fonts}
    ${Imgui__imgui-master__misc__single_file}
    ${Imgui__imgui_sdl-master}
)