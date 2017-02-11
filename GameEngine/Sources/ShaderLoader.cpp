#include "ShaderLoader.h"





//------------------------------ Primary Functions

std::string shader::ShaderLoader::readShader(const std::string& filename)
{
	std::ifstream file(filename, std::ios::in);

	if (!file.good()) {
		std::cout << "Can't read shader file" << filename.c_str() << std::endl;
		std::terminate();
	}

	std::string shader_code;

	file.seekg(0, std::ios::end);
	shader_code.resize(static_cast<unsigned int> (file.tellg()));

	file.seekg(0, std::ios::beg);
	file.read(&shader_code[0], shader_code.size());

	file.close();

	return shader_code;
}

GLuint shader::ShaderLoader::compileShader(GLenum shader_type, const std::string& source_code, const std::string& name)
{
	GLint is_compiled = GL_FALSE;

	GLuint shader = glCreateShader(shader_type);

	if (shader == 0)
		std::cout << "Shader Loader : CREATE SHADER ERROR " << name.c_str() << std::endl;

	const char *shader_code_ptr = source_code.c_str();
	const int   shader_code_size = source_code.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);

	if (is_compiled == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);

		std::cout << "Shader Loader : COMPILE ERROR " << name.c_str() << std::endl << &shader_log[0] << std::endl;
		return 0;
	}

	return shader;
}

void shader::ShaderLoader::createProgram(shader::ShaderFormat* sf)
{
	std::string vertex_shader_code = readShader(sf->getVertexShaderFilename());
	std::string fragment_shader_code = readShader(sf->getFragmentShaderFilename());
	std::string geometry_shader_code = readShader(sf->getGeometryShaderFilename());

	GLuint vertex_shader = compileShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = compileShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");
	GLuint geometry_shader = compileShader(GL_GEOMETRY_SHADER, geometry_shader_code, "geometry shader");

	GLint is_linked = GL_FALSE;

	GLuint program = glCreateProgram();

	if (program == 0)
		std::cout << "Shader Loader : CREATE SHADER PROGRAM ERROR " << sf->getId() << std::endl;

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glAttachShader(program, geometry_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &is_linked);

	if (is_linked == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);

		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteShader(geometry_shader);

	sf->setProgram(program);
}

void shader::ShaderLoader::loadShader(shader::ShaderFormat* sf)
{
	createProgram(sf);
}