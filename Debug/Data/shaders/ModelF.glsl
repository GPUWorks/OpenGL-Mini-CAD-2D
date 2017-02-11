#version 430 core



in VertexData {
    vec2 texCoord;
    vec3 normal;
	flat int baseInstanceARB;
	flat vec3 color;
} VertexIn;

out vec4 color;

layout (binding = 0) uniform sampler2DArray texture0;

void main()
{
    color = vec4(VertexIn.color, 1.0);
}