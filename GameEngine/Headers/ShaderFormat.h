#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include <glew\glew.h>


namespace shader
{
	class ShaderFormat
	{
	private:
		GLuint id;
		std::string vertex_shader_filename;
		std::string fragment_shader_filename;
		std::string geometry_shader_filename;

		GLuint program;

	public:
		//------------------------------ Constructors
		ShaderFormat();
		ShaderFormat(GLuint id, const std::string& vertex_shader_filename, const std::string& fragment_shader_filename, const std::string& geometry_shader_filename);

		//------------------------------ Secondary Functions (Provide Data)
		void setProgram(GLuint program);
		void setId(GLuint id);

		//------------------------------ Secondary Functions (Retrieve Data)
		std::string getVertexShaderFilename();
		std::string getFragmentShaderFilename();
		std::string getGeometryShaderFilename();
		GLuint getProgram();
		GLuint getId();
	};
}