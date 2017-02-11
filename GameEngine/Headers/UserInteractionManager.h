#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Window.h"

#include <GLFW\glfw3.h>


namespace manager
{
	class UserInteractionManager
	{
	private:
		userinteraction::Keyboard* keyboard;
		userinteraction::Mouse* mouse;
		window::Window* window;

		//------------------------------ Constructors
		UserInteractionManager() {};
		~UserInteractionManager() {};

	public:
		//------------------------------ Singleton Pattern
		UserInteractionManager(const UserInteractionManager &) = delete;
		const UserInteractionManager &operator=(const UserInteractionManager &) = delete;
		static UserInteractionManager* getInstance();

		//------------------------------ Primary Functions
		void init(window::Window* window);
		void listener();

		bool isMouseButtonActive(int button);
		bool isMouseButtonPressed(int key);
		bool isKeyPressed(int button);

		glm::vec2 getMouseCursorPosition();
	};
}