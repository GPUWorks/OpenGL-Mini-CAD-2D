#include "Array2DSquareTextureBuffer.h"




//------------------------------ Constructors

storage::Array2DSquareTextureBuffer::Array2DSquareTextureBuffer()
{

}

storage::Array2DSquareTextureBuffer::Array2DSquareTextureBuffer(GLuint mip_level, GLenum sized_internal_format, GLenum base_internal_format, GLuint max_texture_size, GLuint min_texture_size, GLuint layers)
{
	this->mip_level = mip_level;
	this->sized_internal_format = sized_internal_format;
	this->base_internal_format = base_internal_format;
	this->max_texture_size = max_texture_size;
	this->min_texture_size = min_texture_size;
	this->layers = layers;

	
	this->memoryAllocationAndDataInitialization();
	this->generateTextureBuffer();
}


//------------------------------ Secondary Functions

void storage::Array2DSquareTextureBuffer::generateTextureBuffer()
{
	glGenTextures(1, &(this->tbo));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->tbo);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, this->mip_level);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (this->mip_level > 1) {
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, mip_level, this->sized_internal_format, max_texture_size, max_texture_size, layers);
}

void storage::Array2DSquareTextureBuffer::bindTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->tbo);
}


//------------------------------ Secondary Functions (Provide Data)

GLuint storage::Array2DSquareTextureBuffer::insertData(GLuint width, GLuint height, const GLubyte* data)
{
	ds::a2dtbt_seg *node = nullptr;

	for (GLuint i = 0; i < this->layers && node == nullptr; i++)
		node = this->layer_tree[i].search(width);

	if (node == nullptr)
		return 0;

	//glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer, this->max_texture_size, this->max_texture_size, 1, this->base_internal_format, GL_UNSIGNED_BYTE, &clear_data[0]);
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, node->layer, width, height, 1, this->base_internal_format, GL_UNSIGNED_BYTE, data);

	return node->layer;
}


void storage::Array2DSquareTextureBuffer::memoryAllocationAndDataInitialization()
{
	this->layer_tree = new ds::Array2DTextureBufferTree[this->layers];

	for (GLuint i = 0; i < this->layers; i++) {
		this->layer_tree[i] = ds::Array2DTextureBufferTree(this->max_texture_size, this->min_texture_size, i);
	}

	switch (base_internal_format) {
	case GL_RGB:
		this->clear_data = new GLubyte[this->max_texture_size * this->max_texture_size * 3];
		memset(this->clear_data, 0, this->max_texture_size * this->max_texture_size * 3);

		break;
	default:
		this->clear_data = new GLubyte[this->max_texture_size * this->max_texture_size * 4];
		memset(this->clear_data, 0, this->max_texture_size * this->max_texture_size * 4);
	}
}