#pragma once

#include <vector>
#include <set>
#include <iostream>

#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include "VertexFormat.h"
#include "VertexBufferTree.h"


namespace storage
{
	class VertexBuffer
	{
	private:
		GLenum usage;
		GLuint vbo;

		GLuint vertices_no;
		GLuint segment_vertices_no;
		GLuint segments_no;

		GLuint byte_vertex_size;
		GLuint byte_segment_size;
		GLuint byte_buffer_size;

		ds::VertexBufferTree allocator;


	public:
		//------------------------------ Constructors
		VertexBuffer();
		VertexBuffer(GLenum usage, GLuint vertices_no, GLuint segment_vertices_no);

		//------------------------------ Secondary Functions
		void generateBuffer();
		void bindBuffer();

		//------------------------------ Secondary Functions (Provide Data)
		GLint insertData(GLuint vertices_no, const void* data);
		void insertData(GLuint offset, GLuint vertices_no, const void* data);

		//------------------------------ Secondary Functions (Retrieve Data)
		void memoryAllocationAndDataInitialization();

		void clean();
	};
}