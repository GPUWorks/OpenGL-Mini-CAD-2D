#pragma once

#include <GLEW\glew.h>
#include <glm\glm.hpp>


namespace storage
{
	struct IndexBufferSegment
	{
		GLuint start;
		GLuint end;

		//------------------------------ Constructors
		IndexBufferSegment();
		IndexBufferSegment(GLuint start, GLuint end);

		//------------------------------ Secondary Functions (Provide Data)
		void update(GLuint start, GLuint end);
		void update(GLuint end);
	};
}