#include <iostream>

#include "GLEW_Init.h"




core::GLEW_Init::GLEW_Init()
{

}


core::GLEW_Init::GLEW_Init(GLboolean glew_experimental)
{
	glewExperimental = glew_experimental;
}


void core::GLEW_Init::init()
{
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}
	else
	{
		std::cout << "GLEW succesfully initialized" << std::endl;
	}
}