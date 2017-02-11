#pragma once

#include <iostream>
#include <vector>
#include <GLFW\glfw3.h>

/* Number of keys recognized by GLFW when was defined this constant */
#define GLFW_KEYBOARD_KEYS_NUMBER 348

/* Number of maximum code points that can be received per frame */
#define CODE_POINTS_BUFFER_LENGTH 128


namespace userinteraction
{
	class Keyboard
	{
	private:
		static int keys_pressed[GLFW_KEYBOARD_KEYS_NUMBER];
		static std::vector<int> keys_pressed_remove;

		//------------------------------ Static variables
		static unsigned int keys_action[GLFW_KEYBOARD_KEYS_NUMBER];
		static unsigned int keys_scancode[GLFW_KEYBOARD_KEYS_NUMBER];
		static unsigned int keys_modifier_flag[GLFW_KEYBOARD_KEYS_NUMBER];
		
		// Characters Codepoint and Modifier Flag buffers
		static int characters_codepoint[CODE_POINTS_BUFFER_LENGTH];
		static int characters_modifier_flag[CODE_POINTS_BUFFER_LENGTH];
		static unsigned int characters_buffers_number;

	public:
		//------------------------------ Constructors
		Keyboard(GLFWwindow* window);

		//------------------------------ Primary Functions
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void charmodsCallback(GLFWwindow* window, unsigned int codepoint, int mods);

		//------------------------------ Secondary Functions
		static void cleanCharactersBuffers();

		//------------------------------ Secondary Functions (Retrieve Data)
		static int* getKeysPressed();
		static unsigned int* getKeysAction();
		static unsigned int* getKeysScancode();
		static unsigned int* getKeysModifierFlag();
		static int* getCharactersCodepoint();
		static int* getCharactersModifierFlag();
	};
}