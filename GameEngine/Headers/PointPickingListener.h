#pragma once

#include "defcs.h"

#include "ModelManager.h"
#include "UserInteractionManager.h"
#include "CameraManager.h"

#include "Operations.h"


namespace tema1
{
	class PointPickingListener
	{
	private:
		manager::ModelManager* model_manager;

		manager::UserInteractionManager* user_interaction_manager;

		manager::CameraManager* camera_manager;

		Operations* operations;


	public:
		PointPickingListener(manager::ModelManager* model_manager, manager::UserInteractionManager* user_interaction_manager, manager::CameraManager* camera_manager, Operations* operations);

		float getPointLineDistance3D(glm::vec3 p, glm::vec3 lp1, glm::vec3 lp2);

		bool isPointPicked(std::map<model::CurveType, std::vector<model::ModelFormat*>>& models, model::ModelFormat* &model, GLuint &mesh_idx, GLuint &vertex_idx);
		bool isAxisPointPicked(glm::vec3 from, glm::vec3 to);
		GLuint isAxisPicked(model::ModelFormat* model);
	};
}