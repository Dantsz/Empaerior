#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 scale;
    mat4 position;
    mat4 proj;
} ubo;


layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in uint tex_id;
layout(location = 3) in vec3 inColor;

layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out uint  texture_id;
layout(location = 3) out vec3 outColor;


void main() {
    gl_Position = ubo.proj* ubo.position * ubo.scale *  vec4(inPosition,1.0);
	gl_Position.z = inPosition.z;
	texture_id = tex_id;
	fragTexCoord = inTexCoord;
	outColor = inColor;
}