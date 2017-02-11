#version 430 core

//------------------------------ Structure

struct Material
{
	sampler2D diffuse;
    sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//------------------------------ Input

in vec3 Normal;
in vec3 Fragment_position;
in vec2 Texture_coordinates;

//------------------------------ Uniform

uniform vec3 camera_position;
uniform Material material;
uniform Light light;

//------------------------------ Output

out vec4 color;


void main()
{
	// Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, Texture_coordinates));

	// Diffuse
	vec3 normal = normalize(Normal);
	vec3 light_direction = normalize(light.position - Fragment_position);
	float diffuse_strenght = max(dot(normal, light_direction), 0.0f);
	vec3 diffuse = light.diffuse * diffuse_strenght * vec3(texture(material.diffuse, Texture_coordinates));

	// Specular
	vec3 camera_direction = normalize(camera_position - Fragment_position);
	vec3 reflected_ray_direction = reflect(-light_direction, normal);
	float specular_strength = pow(max(dot(camera_direction, reflected_ray_direction), 0.0f), material.shininess);
	vec3 specular = light.specular * specular_strength * vec3(texture(material.specular, Texture_coordinates));

    color = vec4(ambient + diffuse + specular, 1.0f);
}