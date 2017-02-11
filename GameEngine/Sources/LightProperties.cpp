#include "LightProperties.h"




//------------------------------ Constructors

light::LightProperties::LightProperties() { }


//------------------------------ Secondary Functions (Provide Data)

void light::LightProperties::setPosition(glm::vec3 position)
{
	this->position = position;
}

void light::LightProperties::setAmbientColor(glm::vec3 ambient_color)
{
	this->ambient_color = ambient_color;
}

void light::LightProperties::setDiffuseColor(glm::vec3 diffuse_color)
{
	this->diffuse_color = diffuse_color;
}

void light::LightProperties::setSpecularColor(glm::vec3 specular_color)
{
	this->specular_color = specular_color;
}


//------------------------------ Secondary Functions (Retrieve Data)
	
glm::vec3 light::LightProperties::getPosition()
{
	return this->position;
}

glm::vec3 light::LightProperties::getAmbientColor()
{
	return this->ambient_color;
}

glm::vec3 light::LightProperties::getDiffuseColor()
{
	return this->diffuse_color;
}

glm::vec3 light::LightProperties::getSpecularColor()
{
	return this->specular_color;
}
