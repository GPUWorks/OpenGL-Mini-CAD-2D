#include "Keyboard.h"


//------------------------------ Static variables

int userinteraction::Keyboard::keys_pressed[GLFW_KEYBOARD_KEYS_NUMBER] = {};
std::vector<int> userinteraction::Keyboard::keys_pressed_remove = {};

unsigned int userinteraction::Keyboard::keys_action[GLFW_KEYBOARD_KEYS_NUMBER] = {};
unsigned int userinteraction::Keyboard::keys_scancode[GLFW_KEYBOARD_KEYS_NUMBER] = {};
unsigned int userinteraction::Keyboard::keys_modifier_flag[GLFW_KEYBOARD_KEYS_NUMBER] = {};

int userinteraction::Keyboard::characters_codepoint[CODE_POINTS_BUFFER_LENGTH] = {};
int userinteraction::Keyboard::characters_modifier_flag[CODE_POINTS_BUFFER_LENGTH] = {};
unsigned int userinteraction::Keyboard::characters_buffers_number = 0;


//------------------------------ Constructors

userinteraction::Keyboard::Keyboard(GLFWwindow* window)
{
	for (unsigned int i = 0; i < GLFW_KEYBOARD_KEYS_NUMBER; i++) {
		keys_pressed[i] = -1;
	}

	glfwSetKeyCallback(window, keyCallback);

	glfwSetCharModsCallback(window, charmodsCallback);
}


//------------------------------ Primary Functions

void userinteraction::Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << "Key Callback  " << key << std::endl;

	if (key >= 0) {
		if (Keyboard::keys_action[key] == GLFW_PRESS && action == GLFW_RELEASE)
		{
			Keyboard::keys_pressed[key] = GLFW_PRESS;
			Keyboard::keys_pressed_remove.push_back(key);
		}

		Keyboard::keys_action[key] = action;
		Keyboard::keys_scancode[key] = scancode;
		Keyboard::keys_modifier_flag[key] = mods;
	}

}


//------------------------------ Secondary Functions

void userinteraction::Keyboard::cleanCharactersBuffers()
{
	for (unsigned int i = 0; i < CODE_POINTS_BUFFER_LENGTH; i++) {
		Keyboard::characters_codepoint[i] = -1;
		Keyboard::characters_modifier_flag[i] = -1;
	}

	for (int key : Keyboard::keys_pressed_remove)
		Keyboard::keys_pressed[key] = -1;

	Keyboard::keys_pressed_remove.clear();

	Keyboard::characters_buffers_number = 0;
}


void userinteraction::Keyboard::charmodsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
{
	//std::cout << "Character with mods Callback  " << codepoint << std::endl;

	Keyboard::characters_codepoint[Keyboard::characters_buffers_number] = codepoint;
	Keyboard::characters_modifier_flag[Keyboard::characters_buffers_number] = mods;

	Keyboard::characters_buffers_number++;
}


//------------------------------ Secondary Functions (Retrieve Data)

int* userinteraction::Keyboard::getKeysPressed()
{
	return Keyboard::keys_pressed;
}

unsigned int* userinteraction::Keyboard::getKeysAction()
{
	return Keyboard::keys_action;
}

unsigned int* userinteraction::Keyboard::getKeysScancode()
{
	return Keyboard::keys_scancode;
}

unsigned int* userinteraction::Keyboard::getKeysModifierFlag()
{
	return Keyboard::keys_modifier_flag;
}

int* userinteraction::Keyboard::getCharactersCodepoint()
{
	return Keyboard::characters_codepoint;
}

int* userinteraction::Keyboard::getCharactersModifierFlag()
{
	return Keyboard::characters_modifier_flag;
}
