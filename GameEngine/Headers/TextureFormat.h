#pragma once

#include <iostream>
#include <GLEW\glew.h>


namespace texture
{
	class TextureFormat
	{
	
	public:		
		GLuint width;
		GLuint height;
		GLuint channels_no;
		std::string filename;

		GLubyte* data;

	public:
		//------------------------------ Constructors
		TextureFormat();
		TextureFormat(GLuint width, GLuint height, GLuint channels_no, std::string filename, GLubyte* data);
	};
}