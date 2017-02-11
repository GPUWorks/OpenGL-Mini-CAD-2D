#pragma once

#include <glm\glm.hpp>


namespace vertex
{
	class VertexFormat
	{
	public:
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture;

	public:
		//------------------------------ Constructors
		VertexFormat();
		VertexFormat(glm::vec3 position, glm::vec3 normal, glm::vec2 texture);

		//------------------------------ Secondary Functions (Provide Data)
		void setPosition(glm::vec3 position);
		void setNormal(glm::vec3 normal);
		void setTexture(glm::vec2 texture);

		//------------------------------ Secondary Functions (Retrieve Data)
		glm::vec3 getPosition();
		glm::vec3 getNormal();
		glm::vec2 getTexture();
	};
}