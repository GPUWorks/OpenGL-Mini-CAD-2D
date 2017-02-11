#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "StorageManager.h"
#include "ShaderManager.h"
#include "CameraManager.h"


namespace manager
{
	class DrawManager
	{
	private:
		manager::StorageManager* storage_manager;
		manager::ShaderManager* shader_manager;
		manager::CameraManager* camera_manager;

		//------------------------------ Constructors
		DrawManager() {};

	public:
		//------------------------------ Singleton Pattern
		DrawManager(const DrawManager &) = delete;
		const DrawManager &operator=(const DrawManager &) = delete;
		static DrawManager* getInstance();

		//------------------------------ Primary Functions
		void init(manager::StorageManager* stm, manager::ShaderManager* shm, manager::CameraManager* cm);
		void listener();

		void drawModels();
	};
}