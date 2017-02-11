#version 430 core

in vec2 texture_coord;

out vec4 color;

layout (binding = 0) uniform sampler2DArray texture0;

void main()
{
    color = texture(texture0, vec3(texture_coord.x, texture_coord.y, 0));
}