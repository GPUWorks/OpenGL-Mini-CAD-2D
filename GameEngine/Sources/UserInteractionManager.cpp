#include "UserInteractionManager.h"




//------------------------------ Singleton Pattern

manager::UserInteractionManager* manager::UserInteractionManager::getInstance()
{
	static UserInteractionManager instance;

	return &instance;
}


//------------------------------ Primary Functions

void manager::UserInteractionManager::init(window::Window* window)
{
	this->window = window;

	this->keyboard = new userinteraction::Keyboard(this->window->getGLFWWindow());
	this->mouse = new userinteraction::Mouse(this->window->getGLFWWindow());

	userinteraction::Keyboard::cleanCharactersBuffers();
}

void manager::UserInteractionManager::listener()
{
	userinteraction::Keyboard::cleanCharactersBuffers();
	userinteraction::Mouse::cleanBuffers();
}

bool manager::UserInteractionManager::isMouseButtonPressed(int button)
{
	if (this->mouse->getButtonsPressed()[button] == GLFW_PRESS)
		return true;

	return false;
}

bool manager::UserInteractionManager::isKeyPressed(int key)
{
	if (this->keyboard->getKeysPressed()[key] == GLFW_PRESS)
		return true;

	return false;
}

glm::vec2 manager::UserInteractionManager::getMouseCursorPosition()
{
	return this->mouse->getCursorPosition();
}

bool manager::UserInteractionManager::isMouseButtonActive(int button)
{
	if (this->mouse->getButtonsAction()[button] == GLFW_PRESS)
		return true;

	return false;
}