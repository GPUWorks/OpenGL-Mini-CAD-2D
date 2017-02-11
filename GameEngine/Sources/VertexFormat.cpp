#include "VertexFormat.h"


//------------------------------ Constructors

vertex::VertexFormat::VertexFormat()
{

}

vertex::VertexFormat::VertexFormat(glm::vec3 position, glm::vec3 normal, glm::vec2 texture)
{
	this->position = position;
	this->texture = texture;
	this->normal = normal;
}


//------------------------------ Secondary Functions (Provide Data)

void vertex::VertexFormat::setPosition(glm::vec3 position)
{
	this->position = position;	
}

void vertex::VertexFormat::setNormal(glm::vec3 normal)
{
	this->normal = normal;
}

void vertex::VertexFormat::setTexture(glm::vec2 texture)
{
	this->texture = texture;
}


//------------------------------ Secondary Functions (Retrieve Data)

glm::vec3 vertex::VertexFormat::getPosition()
{
	return this->position;
}

glm::vec3 vertex::VertexFormat::getNormal()
{
	return this->normal;
}

glm::vec2 vertex::VertexFormat::getTexture()
{
	return this->texture;
}