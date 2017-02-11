#include "Mouse.h"


//------------------------------ Static variables

int userinteraction::Mouse::buttons_pressed[GLFW_KEYBOARD_BUTTONS_NUMBER] = {};
std::vector<int> userinteraction::Mouse::buttons_pressed_remove = {};

unsigned int userinteraction::Mouse::buttons_action[GLFW_KEYBOARD_BUTTONS_NUMBER] = {};
unsigned int userinteraction::Mouse::buttons_modifier_flag[GLFW_KEYBOARD_BUTTONS_NUMBER] = {};

glm::vec2 userinteraction::Mouse::cursor_position = {};
glm::vec2 userinteraction::Mouse::scroll_offset = {};

//------------------------------ Constructors

userinteraction::Mouse::Mouse(GLFWwindow* window)
{
	for (unsigned int i = 0; i < GLFW_KEYBOARD_BUTTONS_NUMBER; i++) {
		buttons_pressed[i] = -1;
	}

	glfwSetCursorPosCallback(window, cursorPositionCallback);

	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	glfwSetScrollCallback(window, scrollCallback);
}


//------------------------------ Primary Functions

void userinteraction::Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//std::cout << "Mouse Button Callback" << std::endl;

	//std::cout << button << action;

	if (button >= 0) {
		if (Mouse::buttons_action[button] == GLFW_PRESS && action == GLFW_RELEASE)
		{
			Mouse::buttons_pressed[button] = GLFW_PRESS;
			Mouse::buttons_pressed_remove.push_back(button);
		}

		Mouse::buttons_action[button] = action;
		Mouse::buttons_modifier_flag[button] = mods;
	}
}

void userinteraction::Mouse::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "Cursor Position Callback" << std::endl;
	//std::cout << xpos << " " << ypos << std::endl;

	Mouse::cursor_position = { xpos, ypos };
}

void userinteraction::Mouse::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "Scroll Callback" << std::endl;

	Mouse::scroll_offset = { xoffset, yoffset };
}

void userinteraction::Mouse::cleanBuffers()
{
	for (int button : Mouse::buttons_pressed_remove)
		Mouse::buttons_pressed[button] = -1;

	Mouse::buttons_pressed_remove.clear();

	Mouse::scroll_offset = glm::vec2(0, 0);
}


//------------------------------ Secondary Functions (Retrieve Data)

int* userinteraction::Mouse::getButtonsPressed()
{
	return Mouse::buttons_pressed;
}

unsigned int* userinteraction::Mouse::getButtonsAction()
{
	return Mouse::buttons_action;
}

unsigned int* userinteraction::Mouse::getButtonsModifierFlag()
{
	return Mouse::buttons_modifier_flag;
}

glm::vec2 userinteraction::Mouse::getCursorPosition()
{
	return Mouse::cursor_position;
}

glm::vec2 userinteraction::Mouse::getScrollOffset()
{
	return Mouse::scroll_offset;
}