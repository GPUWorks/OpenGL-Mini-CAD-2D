#pragma once

#include "GLEW_Init.h"
#include "GLFW_Init.h"
#include "Window.h"

using namespace core;
using namespace window;


namespace manager
{
	class WindowManager
	{

	private:
		GLFW_Init* glfw;
		GLEW_Init* glew;
		Window* primary_window;

		//------------------------------ Constructors
		WindowManager() {};
		~WindowManager() {};

	public:
		//------------------------------ Singleton Pattern
		WindowManager(const WindowManager &) = delete;
		const WindowManager &operator=(const WindowManager &) = delete;
		static WindowManager* getInstance();

		//------------------------------ Primary Functions
		void init(GLFW_Init* glfw, GLEW_Init* glew);
		void listener();
		void createPrimaryWindow(GLFW_Init* glfw, GLEW_Init* glew);

		//------------------------------ Secondary Functions (Retrieve Data)
		GLFWwindow* getPrimaryWindowGLFW();
		Window* getPrimaryWindow();

	};
}