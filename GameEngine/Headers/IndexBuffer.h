#pragma once

#include <vector>
#include <set>
#include <iostream>

#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include "IndexBufferTree.h"


namespace storage
{
	class IndexBuffer
	{
	private:
		GLenum usage;
		GLuint ebo;

		GLuint indices_no;
		GLuint segment_indices_no;
		GLuint segments_no;

		GLuint byte_index_size;
		GLuint byte_segment_size;
		GLuint byte_buffer_size;

		ds::IndexBufferTree allocator;


	public:
		//------------------------------ Constructors
		IndexBuffer();
		IndexBuffer(GLenum usage, GLuint indices_no, GLuint segment_indices_no);

		//------------------------------ Secondary Functions
		void generateBuffer();
		void bindBuffer();

		//------------------------------ Secondary Functions (Provide Data)
		GLint insertData(GLuint indices_no, const void* data);
		void insertData(GLuint offset, GLuint indices_no, const void* data);

		//------------------------------ Secondary Functions (Retrieve Data)
		void memoryAllocationAndDataInitialization();

		void clean();
	};
}