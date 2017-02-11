#pragma once

#include "defcs.h"

#include "ModelManager.h"
#include "UserInteractionManager.h"
#include "CameraManager.h"

#include "Operations.h"

#include "PlayerCameraCE.h"


namespace tema1
{
	class DragAndDropListener
	{
	private:
		manager::ModelManager* model_manager;

		manager::UserInteractionManager* user_interaction_manager;

		manager::CameraManager* camera_manager;

		Operations* operations;


		
		GLuint mesh_idx;
		GLuint vertex_idx;
		GLuint axis;


	public:
		model::ModelFormat* model = nullptr;
		model::ModelFormat* axisModel = nullptr;

		DragAndDropListener(manager::ModelManager* model_manager, manager::UserInteractionManager* user_interaction_manager, manager::CameraManager* camera_manager, Operations* operations);

		void setPointToProcess(model::ModelFormat* model, GLuint mesh_idx, GLuint vertex_idx, glm::vec2 cursor_position);
		void setAxisToProcess(GLuint axis, model::ModelFormat* axisModel);

		void listener(glm::vec3 mouse_position);

		void reset();
	};
}