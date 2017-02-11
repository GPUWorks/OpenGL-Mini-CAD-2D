#pragma once

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>



#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\norm.hpp>
#include <glm\gtx\transform.hpp>


#ifdef _WIN32
	#define PATH_SEPARATOR '\\'
#elif __linux__
	#define PATH_SEPARATOR '/'
#elif __unix__
	#define PATH_SEPARATOR '/'
#elif __APPLE__ && __MACH__
	#define PATH_SEPARATOR '/'
#endif

#define		MODEL_MANAGER_STARTUP_INFO_FILE			std::string("Data/startup/models_info_file.txt")
#define		SHADER_MANAGER_STARTUP_INFO_FILE		std::string("Data/startup/shaders_info_file.txt")




enum
{
	ENG_CAMERA_ORIENTATION_POSITIVE_AXIS,
	ENG_CAMERA_ORIENTATION_NEGATIVE_AXIS
};