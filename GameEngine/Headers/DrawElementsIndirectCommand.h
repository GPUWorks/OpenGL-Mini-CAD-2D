#pragma once

#include <GLEW\glew.h>
#include <glm\glm.hpp>


namespace storage
{
	struct DrawElementsIndirectCommand
	{
		GLuint count = 0;
		GLuint instance_count = 0;
		GLuint first_index = 0;
		GLuint base_vertex = 0;
		GLuint base_instance = 0;
	};
}