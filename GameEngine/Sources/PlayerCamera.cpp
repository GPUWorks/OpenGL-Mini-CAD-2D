#include "PlayerCamera.h"



//------------------------------ Constructors

player::PlayerCamera::PlayerCamera(glm::vec3 position, GLfloat fovy, GLfloat aspect_ratio, GLfloat znear, GLfloat zfar) : 
	camera::CameraRotation(), camera::CameraTranslation()
{
	// CameraFormat attributes
	this->position = position;

	this->fovy = fovy;
	this->aspect_ratio = aspect_ratio;
	this->znear = znear;
	this->zfar = zfar;
	
	// CameraRotation attributes
	this->y_axis_orientation = NON_INVERTED_Y_AXIS;
	this->mouse_button_2_state = MOUSE_BUTTON_RELEASE;
	this->mouse_sensitivity = MOUSE_SENSITIVITY_MEDIUM;

	// CameraTranslation attributes
	this->movement_speed = MOVEMENT_SPEED_LOW;

	// Compute the projection matrix
	this->updatePerspectiveProjectionMatrix();
	this->updateOrthographicProjectionMatrix();
}


//------------------------------ Primary Functions

void player::PlayerCamera::cameraListener(GLFWwindow* window)
{
	this->lookAroundListener(window);
	this->moveAroundListener();
	this->updateViewMatrix(this->getViewRotationMatrix(), this->getViewTranslationMatrix(&position, view_matrix));
}

void player::PlayerCamera::lookAroundListener(GLFWwindow* window)
{
	
	if (userinteraction::Mouse::getButtonsAction()[GLFW_MOUSE_BUTTON_2] == GLFW_PRESS) {
		if (this->mouse_button_2_state == MOUSE_BUTTON_RELEASE)
			this->mouse_button_2_state = MOUSE_BUTTON_PRESS;
		else if (this->mouse_button_2_state == MOUSE_BUTTON_PRESS)
			this->mouse_button_2_state = MOUSE_BUTTON_REPEAT;

		if (this->mouse_button_2_state == MOUSE_BUTTON_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			this->last_cursor_position = userinteraction::Mouse::getCursorPosition();
			this->cursor_position_on_mouse_button_2_press = userinteraction::Mouse::getCursorPosition();
		}
		else if (this->mouse_button_2_state == MOUSE_BUTTON_REPEAT) {
			this->delta_cursor_position = userinteraction::Mouse::getCursorPosition() - this->last_cursor_position;
			this->last_cursor_position = userinteraction::Mouse::getCursorPosition();

			this->updateYawAngle(this->delta_cursor_position.x * this->mouse_sensitivity);
			this->updatePitchAngle(this->delta_cursor_position.y * this->mouse_sensitivity * this->y_axis_orientation);
		}

		this->resetCursorOnMouseButton2HoldListener(window);
	}
	else {
		if (this->mouse_button_2_state != MOUSE_BUTTON_RELEASE) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetCursorPos(window, cursor_position_on_mouse_button_2_press.x, cursor_position_on_mouse_button_2_press.y);
			this->mouse_button_2_state = MOUSE_BUTTON_RELEASE;
		}
	}
}

void player::PlayerCamera::resetCursorOnMouseButton2HoldListener(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	if (userinteraction::Mouse::getCursorPosition().x < 0 || userinteraction::Mouse::getCursorPosition().x > width ||
		userinteraction::Mouse::getCursorPosition().y < 0 || userinteraction::Mouse::getCursorPosition().y > height) {

		glfwSetCursorPos(window, width / 2, height / 2);
		this->last_cursor_position = glm::vec2(width / 2, height / 2);
	}
}

void player::PlayerCamera::moveAroundListener()
{
	resetXAxisTranslationStep();
	resetZAxisTranslationStep();

	if (userinteraction::Keyboard::getKeysAction()[GLFW_KEY_A])
		this->updateXAxisTranslationStep(ENG_CAMERA_ORIENTATION_NEGATIVE_AXIS, movement_speed);
	if (userinteraction::Keyboard::getKeysAction()[GLFW_KEY_D])
		this->updateXAxisTranslationStep(ENG_CAMERA_ORIENTATION_POSITIVE_AXIS, movement_speed);

	if (userinteraction::Keyboard::getKeysAction()[GLFW_KEY_W])
		this->updateZAxisTranslationStep(ENG_CAMERA_ORIENTATION_NEGATIVE_AXIS, movement_speed);
	if (userinteraction::Keyboard::getKeysAction()[GLFW_KEY_S])
		this->updateZAxisTranslationStep(ENG_CAMERA_ORIENTATION_POSITIVE_AXIS, movement_speed);
}