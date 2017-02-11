#include "GLFW_Init.h"




core::GLFW_Init::GLFW_Init()
{

}


core::GLFW_Init::GLFW_Init(int major_version, int minor_version, int opengl_profile, int msaa_factor)
{
	this->major_context_version = major_version;
	this->minor_context_version = minor_version;
	this->opengl_profile = opengl_profile;
	this->msaa_factor = msaa_factor;
}



void core::GLFW_Init::init()
{
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, msaa_factor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->major_context_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->minor_context_version);
	glfwWindowHint(GLFW_OPENGL_PROFILE, this->opengl_profile);
}