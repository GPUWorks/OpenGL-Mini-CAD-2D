#version 430 core


//------------------------------ Input

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture_coordinates;

//------------------------------ Uniform

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//------------------------------ Output

out vec3 Normal;
out vec3 Fragment_position;
out vec2 Texture_coordinates;


void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
	Fragment_position = vec3(model * vec4(position, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;
    Texture_coordinates = texture_coordinates;
}