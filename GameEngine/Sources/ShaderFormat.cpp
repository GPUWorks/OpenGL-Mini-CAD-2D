#include "ShaderFormat.h"


//------------------------------ Constructors

shader::ShaderFormat::ShaderFormat() { }

shader::ShaderFormat::ShaderFormat(GLuint id, const std::string& vertex_shader_filename, const std::string& fragment_shader_filename, const std::string& geometry_shader_filename)
{
	this->id = id;
	this->vertex_shader_filename = vertex_shader_filename;
	this->fragment_shader_filename = fragment_shader_filename;
	this->geometry_shader_filename = geometry_shader_filename;
}


//------------------------------ Secondary Functions (Provide Data)
void shader::ShaderFormat::setProgram(GLuint program)
{
	this->program = program;
}

void shader::ShaderFormat::setId(GLuint id)
{
	this->id = id;
}

//------------------------------ Secondary Functions (Retrieve Data)

std::string shader::ShaderFormat::getVertexShaderFilename()
{
	return this->vertex_shader_filename;
}

std::string shader::ShaderFormat::getFragmentShaderFilename()
{
	return this->fragment_shader_filename;
}

std::string shader::ShaderFormat::getGeometryShaderFilename()
{
	return this->geometry_shader_filename;
}

GLuint shader::ShaderFormat::getProgram()
{
	return this->program;
}

GLuint shader::ShaderFormat::getId()
{
	return this->id;
}