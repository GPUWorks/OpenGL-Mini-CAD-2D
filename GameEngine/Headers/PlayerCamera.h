#pragma once

#include "defcs.h"

#include "CameraFormat.h"
#include "CameraRotation.h"
#include "CameraTranslation.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "Window.h"

#include "FrameFormat.h"
#include "PlayerCameraCE.h"


namespace player
{
	

	class PlayerCamera :	public camera::CameraFormat,
							private camera::CameraRotation,
							private camera::CameraTranslation
	{
	private:
		// Camera Rotation
		GLfloat mouse_sensitivity;
		GLint y_axis_orientation;
		EMouseButtonAction mouse_button_2_state;

		glm::vec2 cursor_position_on_mouse_button_2_press;
		glm::vec2 last_cursor_position;
		glm::vec2 delta_cursor_position;

		// Camera Translation
		GLfloat movement_speed;



		//------------------------------ Primary Functions
		void lookAroundListener(GLFWwindow* window);
		void moveAroundListener();
		void resetCursorOnMouseButton2HoldListener(GLFWwindow* window);

	public:
		//------------------------------ Constructors
		PlayerCamera(glm::vec3 position, GLfloat fovy, GLfloat aspect_ratio, GLfloat znear, GLfloat zfar);

		//------------------------------ Primary Functions
		void cameraListener(GLFWwindow* window);
		
	};
}