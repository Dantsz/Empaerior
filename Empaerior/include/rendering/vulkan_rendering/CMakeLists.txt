set(vulkan_rendering
"include/rendering/vulkan_rendering/renderer.h"
"src/rendering/vulkan_rendering/renderer.cpp"

"include/rendering/vulkan_rendering/camera.h"
"include/rendering/vulkan_rendering/texture_atlas.h"
"include/rendering/vulkan_rendering/geometry_buffer.h"
"include/rendering/vulkan_rendering/misc_functions.h"
"include/rendering/vulkan_rendering/sprite.h"
"include/rendering/vulkan_rendering/glyphs.h"
"include/rendering/vulkan_rendering/vertex.h"
"include/rendering/vulkan_rendering/scene.h"
"src/rendering/vulkan_rendering/sprite.cpp"
"src/rendering/vulkan_rendering/texture_atlas.cpp"
"src/rendering/vulkan_rendering/misc_functions.cpp"
"src/rendering/vulkan_rendering/glyphs.cpp"
"src/rendering/vulkan_rendering/scene.cpp"
"include/rendering/vulkan_rendering/graphic_settings.h"
)
source_group(rendering\\vulkan_rendering FILES ${vulkan_rendering})