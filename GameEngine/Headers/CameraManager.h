#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "PlayerCamera.h"


namespace manager
{
	class CameraManager
	{
	private:
		player::PlayerCamera* player_camera;

		//------------------------------ Constructors
		CameraManager() {};
		~CameraManager() {};

	public:
		//------------------------------ Singleton Pattern
		CameraManager(const CameraManager &) = delete;
		const CameraManager &operator=(const CameraManager &) = delete;
		static CameraManager* getInstance();

		//------------------------------ Primary Functions
		void init(GLFWwindow* window);
		void listener(GLFWwindow* window);
		void playerCameraListener(GLFWwindow* window);

		//------------------------------ Secondary Functions (Provide Data)
		void setPlayerCamera(player::PlayerCamera* player_camera);
		void setPlayerCameraUniforms(GLuint program);

		//------------------------------ Secondary Functions (Retrieve Data)
		player::PlayerCamera* getPlayerCamera();
	};
}