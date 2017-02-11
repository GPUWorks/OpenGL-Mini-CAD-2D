#include "ShaderManager.h"




//------------------------------ Singleton Pattern

manager::ShaderManager* manager::ShaderManager::getInstance()
{
	static ShaderManager instance;

	return &instance;
}


//------------------------------ Primary Functions

void manager::ShaderManager::init(std::string exec_path)
{
	this->exec_path = exec_path;
	this->processShadersInfoFile(exec_path + SHADER_MANAGER_STARTUP_INFO_FILE);
}


//------------------------------ Secondary Functions (Provide Data)

void manager::ShaderManager::add(GLuint shader_id, const std::string& vertex_shader_file_path, const std::string& fragment_shader_file_path, const std::string& geometry_shader_file_path)
{
	shader::ShaderFormat* sf = new shader::ShaderFormat(shader_id, vertex_shader_file_path, fragment_shader_file_path, geometry_shader_file_path);
	shader::ShaderLoader::loadShader(sf);

	this->shaders[shader_id] = sf;
}


//------------------------------ Secondary Functions (Retrieve Data)

shader::ShaderFormat* manager::ShaderManager::getShader(GLuint shader_id)
{
	return this->shaders[shader_id];
}


//------------------------------ Secondary Functions (Remove Data)

void manager::ShaderManager::removeShader(GLuint shader_id)
{
	glDeleteProgram(this->shaders[shader_id]->getProgram());

	delete this->shaders[shader_id];

	this->shaders.erase(shader_id);
}



void manager::ShaderManager::processShadersInfoFile(std::string file_path)
{
	std::ifstream shaders_info_file(file_path, std::ifstream::in);
	GLuint shader_groups_no;
	std::string flag;
	GLint shader_id = -1;
	std::string vertex_file_path;
	std::string fragment_file_path;
	std::string geometry_file_path;

	if (shaders_info_file.is_open())
	{
		shaders_info_file >> shader_groups_no;

		while (!shaders_info_file.eof())
		{
			shaders_info_file >> flag;

			if (!flag.compare("-i"))
			{
				if (shader_id > -1)
				{
					this->add(shader_id, exec_path + vertex_file_path, exec_path + fragment_file_path, exec_path + geometry_file_path);
				}

				shaders_info_file >> shader_id;
			}
			else if (!flag.compare("-v"))
			{
				shaders_info_file >> vertex_file_path;
			}
			else if (!flag.compare("-f"))
			{
				shaders_info_file >> fragment_file_path;
			}
			else if (!flag.compare("-g"))
			{
				shaders_info_file >> geometry_file_path;
			}
		}

		this->add(shader_id, exec_path + vertex_file_path, exec_path + fragment_file_path, exec_path + geometry_file_path);
	}
}