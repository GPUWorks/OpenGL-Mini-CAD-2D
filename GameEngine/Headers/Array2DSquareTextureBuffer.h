#pragma once

#include <vector>

#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include "Array2DTextureBufferTree.h"


namespace storage
{
	class Array2DSquareTextureBuffer
	{
	private:
		GLuint tbo;

		GLuint mip_level;
		GLenum sized_internal_format;
		GLenum base_internal_format;
		GLuint max_texture_size;
		GLuint min_texture_size;
		GLuint layers;

		ds::Array2DTextureBufferTree *layer_tree;

		GLubyte* clear_data;

		//------------------------------ Secondary Functions
		void generateTextureBuffer();


	public:
		//------------------------------ Constructors
		Array2DSquareTextureBuffer();
		Array2DSquareTextureBuffer(GLuint mip_level, GLenum sized_internal_format, GLenum base_internal_format, GLuint max_texture_size, GLuint min_texture_size, GLuint layers);

		//------------------------------ Secondary Functions
		void bindTexture();

		//------------------------------ Secondary Functions (Provide Data)
		GLuint insertData(GLuint width, GLuint height, const GLubyte* data);

		void memoryAllocationAndDataInitialization();
	};
}