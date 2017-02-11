#include "WindowManager.h"




//------------------------------ Singleton Pattern

manager::WindowManager* manager::WindowManager::getInstance()
{
	static WindowManager instance;

	return &instance;
}


//------------------------------ Primary Functions

void manager::WindowManager::init(GLFW_Init* glfw, GLEW_Init* glew)
{
	this->glfw = glfw;
	this->glew = glew;
	
	this->createPrimaryWindow(this->glfw, this->glew);
}

void manager::WindowManager::listener()
{

}

void manager::WindowManager::createPrimaryWindow(GLFW_Init* glfw, GLEW_Init* glew)
{
	this->glfw->init();
	this->primary_window = new Window();
	this->primary_window->init();
	this->glew->init();

	glViewport(0, 0, primary_window->getWidth(), primary_window->getHeight());
}


//------------------------------ Secondary Functions (Retrieve Data)

GLFWwindow* manager::WindowManager::getPrimaryWindowGLFW()
{
	return this->primary_window->getGLFWWindow();
}

Window* manager::WindowManager::getPrimaryWindow()
{
	return this->primary_window;
}