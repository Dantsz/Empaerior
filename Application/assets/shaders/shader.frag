#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : enable


layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in flat uint texture_id;
layout(location = 3) in vec3 inColor;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform UniformBufferObject {
    mat4 scale;
    mat4 position;
    mat4 proj;
} ubo;

layout(binding = 1) uniform sampler texSampler;
layout(binding = 2) uniform texture2D textures[];


void main() {

	
	vec2 dPdx = dFdx( fragTexCoord );
	vec2 dPdy = dFdy( fragTexCoord );
	vec4 texColor = textureGrad(sampler2D(textures[nonuniformEXT(texture_id)], texSampler), fragTexCoord , dPdx,dPdy);
	
	
    outColor =  texColor + vec4(inColor,0);

	if(outColor.w < 0.2) discard;
	
}