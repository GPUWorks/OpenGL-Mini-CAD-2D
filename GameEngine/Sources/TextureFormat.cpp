#include <TextureFormat.h>


//------------------------------ Constructors

texture::TextureFormat::TextureFormat()
{

}

texture::TextureFormat::TextureFormat(GLuint width, GLuint height, GLuint channels_no, std::string filename, GLubyte* data)
{
	this->width = width;
	this->height = height;
	this->channels_no = channels_no;
	this->filename = filename;
	this->data = data;
}