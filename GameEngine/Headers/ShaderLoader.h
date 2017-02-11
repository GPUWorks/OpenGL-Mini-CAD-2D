#pragma once


#include "ShaderFormat.h"


namespace shader
{
	class ShaderLoader
	{
	private:
		//------------------------------ Constructors
		ShaderLoader() {};

		//------------------------------ Primary Functions
		static std::string readShader(const std::string& filename);
		static GLuint compileShader(GLenum shader_type, const std::string& source_code, const std::string& name);
		static void createProgram(shader::ShaderFormat* sf);

	public:
		//------------------------------ Primary Functions
		static void loadShader(shader::ShaderFormat* sf);
		
	};
}