#version 430 core

#extension GL_ARB_shader_draw_parameters: require

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VertexData {
    vec2 texCoord;
    vec3 normal;
	int baseInstanceARB;
	int instance;
} VertexOut;


void main()
{
	VertexOut.texCoord = texture;
    VertexOut.normal = normal;
	VertexOut.baseInstanceARB = gl_BaseInstanceARB;
	VertexOut.instance = gl_InstanceID;

    gl_Position = vec4(position, 1.0f);
}