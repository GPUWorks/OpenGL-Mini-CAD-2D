#pragma once

#include <GLEW\glew.h>
#include <glm\glm.hpp>


namespace light
{
	class LightProperties
	{
	private:
		glm::vec3 position;

		glm::vec3 ambient_color;
		glm::vec3 diffuse_color;
		glm::vec3 specular_color;

		//------------------------------ Constructors
		LightProperties();

	public:
		//------------------------------ Secondary Functions (Provide Data)
		void setPosition(glm::vec3 position);
		void setAmbientColor(glm::vec3 ambient_color);
		void setDiffuseColor(glm::vec3 diffuse_color);
		void setSpecularColor(glm::vec3 specular_color);

		//------------------------------ Secondary Functions (Retrieve Data)
		glm::vec3 getPosition();
		glm::vec3 getAmbientColor();
		glm::vec3 getDiffuseColor();
		glm::vec3 getSpecularColor();
	};
}