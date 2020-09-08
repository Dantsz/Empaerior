set(vulkan_rendering
"include/rendering/vulkan_rendering/renderer.h"
"Src/rendering/vulkan_rendering/renderer.cpp"

"include/rendering/vulkan_rendering/camera.h"
"include/rendering/vulkan_rendering/texture_atlas.h"
"include/rendering/vulkan_rendering/geometry_buffer.h"
"include/rendering/vulkan_rendering/misc_functions.h"
"include/rendering/vulkan_rendering/sprite.h"
"include/rendering/vulkan_rendering/glyphs.h"
"Src/rendering/vulkan_rendering/sprite.cpp"
"Src/rendering/vulkan_rendering/texture_atlas.cpp"
"Src/rendering/vulkan_rendering/misc_functions.cpp"
"include/rendering/vulkan_rendering/graphic_settings.h"
)
source_group(rendering\\vulkan_rendering FILES ${vulkan_rendering})