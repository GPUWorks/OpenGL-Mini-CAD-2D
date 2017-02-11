#include "TextureDataStorage.h"



//------------------------------ Constructors

storage::TextureDataStorage::TextureDataStorage()
{

}

storage::TextureDataStorage::TextureDataStorage(GLuint mip_level, GLenum sized_internal_format, GLenum base_internal_format, GLuint width, GLuint height, GLuint min_texture_size, GLuint layers)
{
	if (width == height)
		this->array_2d_square_texture_buffer = storage::Array2DSquareTextureBuffer(mip_level, sized_internal_format, base_internal_format, width, min_texture_size, layers);
}

storage::Array2DSquareTextureBuffer storage::TextureDataStorage::getArray2DSquareTextureBuffer()
{
	return this->array_2d_square_texture_buffer;
}


void storage::TextureDataStorage::addModelTexture(model::ModelFormat* model)
{
	this->array_2d_square_texture_buffer.bindTexture();

	for (mesh::MeshFormat* mesh : model->meshes) {
		//mesh->model_property.texture_array_index = this->array_2d_square_texture_buffer.insertData(mesh->textures[texture::TEXTURE_DIFFUSE]->width,
			//mesh->textures[texture::TEXTURE_DIFFUSE]->height, &(mesh->textures[texture::TEXTURE_DIFFUSE]->data[0]));
	}
}