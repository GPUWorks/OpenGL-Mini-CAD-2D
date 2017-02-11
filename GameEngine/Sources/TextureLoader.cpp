#include "TextureLoader.h"



//------------------------------ Primary Functions

texture::TextureFormat* texture::TextureLoader::loadImage(std::string filename)
{
	GLint texture_width;
	GLint texture_height;
	GLint channels_no;

	GLubyte* texture_data = SOIL_load_image(filename.c_str(), &texture_width, &texture_height, &channels_no, SOIL_LOAD_RGB);

	if (!texture_data)
		std::cout << "Failed to load Texture" << std::endl;

	texture::TextureFormat* tf = new texture::TextureFormat(texture_width, texture_height, channels_no, filename, texture_data);

	return tf;
}