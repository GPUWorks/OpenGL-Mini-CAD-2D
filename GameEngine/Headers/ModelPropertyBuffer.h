#pragma once

#include <vector>

#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include "ModelPropertyBufferSegment.h"
#include "ModelProperty.h"


namespace storage
{
	class ModelPropertyBuffer
	{
	private:
		GLuint ssbo;

		GLuint size;
		GLuint segments_no;
		GLenum usage;
		GLuint binding_point;

		GLuint property_size;

		storage::ModelPropertyBufferSegment** all_segments;
		std::vector<storage::ModelPropertyBufferSegment*> free_segments;

	public:
		//------------------------------ Constructors
		ModelPropertyBuffer();
		ModelPropertyBuffer(GLenum usage, GLuint buffer_size, GLuint property_size, GLuint binding_point);

		//------------------------------ Secondary Functions
		void bindBuffer();

		//------------------------------ Secondary Functions (Provide Data)
		GLuint insertData(GLuint segment_position, const void* data);
		GLuint getBindingPoint();

		void clean();
	};
}