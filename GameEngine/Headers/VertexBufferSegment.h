#pragma once

#include <GLEW\glew.h>
#include <glm\glm.hpp>


namespace storage
{
	struct VertexBufferSegment
	{
		GLuint start;
		GLuint end;

		//------------------------------ Constructors
		VertexBufferSegment();
		VertexBufferSegment(GLuint start, GLuint end);

		//------------------------------ Secondary Functions (Provide Data)
		void update(GLuint start, GLuint end);
		void update(GLuint end);
	};
}