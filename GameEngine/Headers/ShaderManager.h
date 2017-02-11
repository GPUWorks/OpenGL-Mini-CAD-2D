#pragma once

#include "defcs.h"

#include <map>
#include <string>
#include <fstream>

#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include "ShaderFormat.h"
#include "ShaderLoader.h"


namespace manager
{
	class ShaderManager
	{
	private:
		std::map<GLuint, shader::ShaderFormat*> shaders;
		std::string exec_path;

		//------------------------------ Constructors
		ShaderManager() {};
		~ShaderManager() {};

	public:
		//------------------------------ Singleton Pattern
		ShaderManager(const ShaderManager &) = delete;
		const ShaderManager &operator=(const ShaderManager &) = delete;
		static ShaderManager* getInstance();

		//------------------------------ Primary Functions
		void init(std::string exec_path);

		//------------------------------ Secondary Functions (Provide Data)
		void add(GLuint shader_id, const std::string& vertex_shader_file_path, const std::string& fragment_shader_file_path, const std::string& geometry_shader_file_path);

		//------------------------------ Secondary Functions (Retrieve Data)
		shader::ShaderFormat* getShader(GLuint shader_id);

		//------------------------------ Secondary Functions (Remove Data)
		void removeShader(GLuint shader_id);


		void processShadersInfoFile(std::string file_path);
	};
}