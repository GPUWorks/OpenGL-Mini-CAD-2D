#pragma once

#include "Array2DSquareTextureBuffer.h"
#include "ModelFormat.h"


namespace storage
{
	class TextureDataStorage
	{
	private:
		storage::Array2DSquareTextureBuffer array_2d_square_texture_buffer;

	public:
		//------------------------------ Constructors
		TextureDataStorage();
		TextureDataStorage(GLuint mip_level, GLenum sized_internal_format, GLenum base_internal_format, GLuint width, GLuint height, GLuint min_texture_size, GLuint layers);

		storage::Array2DSquareTextureBuffer getArray2DSquareTextureBuffer();
		void addModelTexture(model::ModelFormat* model);
	};
}