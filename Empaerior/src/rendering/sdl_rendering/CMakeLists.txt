set(sdl_rendering
"Src/rendering/sdl_rendering/sdl_renderer.h"
"Src/rendering/sdl_rendering/sdl_renderer.cpp"
"Src/rendering/sdl_rendering/sprite_system.h"
"Src/rendering/sdl_rendering/sprite_system.cpp"
"Src/rendering/sdl_rendering/assetmanager.h"
"Src/rendering/sdl_rendering/assetmanager.cpp"
)

set(rendering__objects
    "Src/rendering/sdl_rendering/objects/sprite.cpp"
    "Src/rendering/sdl_rendering/objects/sprite.h"
)
source_group("rendering\\sdl_rendering\\objects" FILES ${rendering__objects})

source_group("rendering\\sdl_rendering" FILES ${sdl_rendering})


set(rendering__sdlwrappers
    "Src/rendering/sdl_rendering/sdlwrappers/ptr_wrappers.h"
    "Src/rendering/sdl_rendering/sdlwrappers/rendering_wrappers.h"
    "Src/rendering/sdl_rendering/sdlwrappers/sdl_wrappers.h"
)
source_group("rendering\\sdl_rendering\\sdlwrappers" FILES ${rendering__sdlwrappers})

set(sdl_rendering__glyphs
    "Src/rendering/sdl_rendering/glyphs/glyphs.cpp"
    "Src/rendering/sdl_rendering/glyphs/glyphs.h"
)
source_group("rendering\\sdl_rendering\\glyphs" FILES ${sdl_rendering__glyphs})



set(sdl_rendering

${sdl_rendering__glyphs}
${rendering__sdlwrappers}
${sdl_rendering}
${rendering__objects}

)