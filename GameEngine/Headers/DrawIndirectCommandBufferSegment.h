#pragma once

#include <GLEW\glew.h>
#include <glm\glm.hpp>


namespace storage
{
	struct DrawIndirectCommandBufferSegment
	{
		GLuint start;

		//------------------------------ Constructors
		DrawIndirectCommandBufferSegment();
		DrawIndirectCommandBufferSegment(GLuint start);

		//------------------------------ Secondary Functions (Provide Data)
		void update(GLuint start);
	};
}