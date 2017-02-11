#include <iostream>

#include "Window.h"


//------------------------------ Constructors

window::Window::Window()
{
	this->width = 800;
	this->height = 600;
	this->title = "Default title";
	this->monitor = nullptr;
	this->share = nullptr;
	this->resizeable = false;
}

window::Window::Window(GLuint width, GLuint height, char* title, GLFWmonitor* monitor, GLFWwindow* share, bool resizeable)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->monitor = monitor;
	this->share = share;
	this->resizeable = resizeable;
}


//------------------------------ Primary Functions

void window::Window::init()
{
	glfwWindowHint(GLFW_RESIZABLE, resizeable);

	this->glfw_window = glfwCreateWindow(width, height, title, monitor, share);

	if (glfw_window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	else
	{
		std::cout << "GLFW window succesfully created" << std::endl;
	}

	glfwMakeContextCurrent(this->glfw_window);
}


//------------------------------ Secondary Functions (Provide Data)

void window::Window::setDimension(GLuint width, GLuint height)
{
	this->width = width;
	this->height = height;
}

void window::Window::setWidth(GLuint width)
{
	this->width = width;
}

void window::Window::setHeight(GLuint height)
{
	this->height = height;
}

void window::Window::setTitle(char* title)
{
	this->title = title;
}

void window::Window::setMonitor(GLFWmonitor* monitor)
{
	this->monitor = monitor;
}

void window::Window::setSharedWindow(GLFWwindow* share)
{
	this->share = share;
}

void window::Window::setResizeable(bool resizeable)
{
	this->resizeable = resizeable;
}


//------------------------------ Secondary Functions (Retrieve Data)

GLuint window::Window::getWidth()
{
	return this->width;
}

GLuint window::Window::getHeight()
{
	return this->height;
}

char* window::Window::getTitle()
{
	return this->title;
}

bool window::Window::isResizeable()
{
	return this->resizeable;
}

GLFWwindow* window::Window::getGLFWWindow()
{
	return this->glfw_window;
}