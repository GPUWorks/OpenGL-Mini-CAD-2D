#pragma once

#include <GLEW\glew.h>
#include <glm\glm.hpp>


namespace storage
{
	struct ModelPropertyBufferSegment
	{
		GLuint position;
		GLuint end;

		//------------------------------ Constructors
		ModelPropertyBufferSegment();
		ModelPropertyBufferSegment(GLuint position);

		void update(GLuint position);
	};
}