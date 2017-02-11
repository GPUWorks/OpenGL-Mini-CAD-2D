#pragma once

#include <GLEW\glew.h>
#include <glm\glm.hpp>




namespace player
{
	// Camera Rotation
	enum EMouseButtonAction {
		MOUSE_BUTTON_RELEASE = 0,
		MOUSE_BUTTON_PRESS = 1,
		MOUSE_BUTTON_REPEAT = 2
	};

	const GLint INVERTED_Y_AXIS = -1;
	const GLint NON_INVERTED_Y_AXIS = 1;

	const GLfloat MOUSE_SENSITIVITY_HIGH = 0.15f;
	const GLfloat MOUSE_SENSITIVITY_MEDIUM = 0.1f;
	const GLfloat MOUSE_SENSITIVITY_LOW = 0.05f;


	// Camera Translation
	const GLfloat MOVEMENT_SPEED_HIGH = 10;
	const GLfloat MOVEMENT_SPEED_MEDIUM = 7;
	const GLfloat MOVEMENT_SPEED_LOW = 1;
}