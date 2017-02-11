#pragma once

#include "defcs.h"

#include "ModelManager.h"
#include "UserInteractionManager.h"
#include "CameraManager.h"


namespace tema1
{
	class Operations
	{
	private:
		manager::ModelManager* model_manager;

		manager::UserInteractionManager* user_interaction_manager;

		manager::CameraManager* camera_manager;


	public:
		Operations(manager::ModelManager* model_manager, manager::UserInteractionManager* user_interaction_manager, manager::CameraManager* camera_manager);


		glm::vec3 getMousePosInWorldCoord(float z);
	};
}