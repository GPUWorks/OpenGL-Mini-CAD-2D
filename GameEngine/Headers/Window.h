#pragma once

#include <GLFW\glfw3.h>


namespace window
{
	class Window
	{

	private:
		GLFWwindow* glfw_window = nullptr;

		GLuint width;
		GLuint height;
		char* title;
		GLFWmonitor* monitor;
		GLFWwindow* share;
		bool resizeable;

	public:
		//------------------------------ Constructors
		Window();
		Window(GLuint width, GLuint height, char* title, GLFWmonitor* monitor, GLFWwindow* share, bool resizeable);
		
		//------------------------------ Primary Functions
		void init();

		//------------------------------ Secondary Functions (Provide Data)
		void setDimension(GLuint width, GLuint height);
		void setWidth(GLuint width);
		void setHeight(GLuint height);
		void setTitle(char* title);
		void setMonitor(GLFWmonitor* monitor);
		void setSharedWindow(GLFWwindow* share);
		void setResizeable(bool resizeable);

		//------------------------------ Secondary Functions (Retrieve Data)
		GLuint getWidth();
		GLuint getHeight();
		char* getTitle();
		bool isResizeable();

		GLFWwindow* getGLFWWindow();
	};
}