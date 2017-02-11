#pragma once

#include "defcs.h"

#include "ModelManager.h"
#include "UserInteractionManager.h"
#include "CameraManager.h"

#include "Operations.h"

#include "PointPickingListener.h"

#include "DragAndDropListener.h"

#include "CurvesAndSurfaces.h"


namespace manager
{
	class T1Manager
	{
	private:
		//------------------------------ Constructors
		T1Manager() {};
		~T1Manager() {};

		ModelManager* model_manager;

		UserInteractionManager* user_interaction_manager;

		CameraManager* camera_manager;


		tema1::Operations* operations;

		tema1::PointPickingListener* point_picking_listener;

		tema1::DragAndDropListener* drag_and_drop_listener;

		tema1::CurvesAndSurfaces* curves_and_surfaces;

		bool isEditMode = false;
		bool isPointPicked = false;
		bool isAxisPicked = false;
		bool isExistingModelPicked = false;

		glm::vec3 current_mouse_pos = glm::vec3(0.0, 0.0, 0.0);
		glm::vec3 last_mouse_pos = glm::vec3(0.0, 0.0, 0.0);

		model::CurveType current_curve_type = model::NONE;


	public:
		//------------------------------ Singleton Pattern
		T1Manager(const T1Manager &) = delete;
		const T1Manager &operator=(const T1Manager &) = delete;
		static T1Manager* getInstance();

		//------------------------------ Primary Functions
		void init(ModelManager* model_manager, UserInteractionManager* user_interaction_manager, CameraManager* camera_manager);
		void listener();
	};
}