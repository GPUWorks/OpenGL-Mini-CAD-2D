#pragma once

#include <iostream>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <vector>

/* Number of mouse buttons recognized by GLFW when was defined this constant */
#define GLFW_KEYBOARD_BUTTONS_NUMBER 7


namespace userinteraction
{
	class Mouse
	{
	private:
		static int buttons_pressed[GLFW_KEYBOARD_BUTTONS_NUMBER];
		static std::vector<int> buttons_pressed_remove;

		//------------------------------ Static variables
		static unsigned int buttons_action[GLFW_KEYBOARD_BUTTONS_NUMBER];
		static unsigned int buttons_modifier_flag[GLFW_KEYBOARD_BUTTONS_NUMBER];

		static glm::vec2 cursor_position;
		static glm::vec2 scroll_offset;

	public:
		//------------------------------ Constructors
		Mouse(GLFWwindow* window);

		//------------------------------ Primary Functions
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		static void cleanBuffers();

		//------------------------------ Secondary Functions (Retrieve Data)
		static int* getButtonsPressed();
		static unsigned int* getButtonsAction();
		static unsigned int* getButtonsModifierFlag();
		static glm::vec2 getCursorPosition();
		static glm::vec2 getScrollOffset();

	};
}