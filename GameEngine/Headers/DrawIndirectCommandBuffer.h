#pragma once

#include <vector>
#include <set>
#include <iostream>

#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include "DrawIndirectCommandBufferTree.h"
#include "DrawElementsIndirectCommand.h"



namespace storage
{
	class DrawIndirectCommandBuffer
	{
	private:
		GLenum usage;
		GLuint dibo;

		GLuint indirect_commands_no;
		GLuint segments_no;

		GLuint byte_indirect_command_size;
		GLuint byte_segment_size;
		GLuint byte_buffer_size;

		ds::DrawIndirectCommandBufferTree allocator;

		storage::DrawElementsIndirectCommand* clear_data;


	public:
		//------------------------------ Constructors
		DrawIndirectCommandBuffer();
		DrawIndirectCommandBuffer(GLenum usage, GLuint indirect_commands_no);

		//------------------------------ Secondary Functions
		void generateBuffer();
		void bindBuffer();

		//------------------------------ Secondary Functions (Provide Data)
		GLint insertData(const void* data);
		void insertData(GLuint offset, const void* data);

		//------------------------------ Secondary Functions (Retrieve Data)
		GLuint getActiveIndirectCommandsNo();
		void memoryAllocationAndDataInitialization();

		void clean();
	};
}