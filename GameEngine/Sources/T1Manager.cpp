#include "T1Manager.h"






//------------------------------ Singleton Pattern

manager::T1Manager* manager::T1Manager::getInstance()
{
	static T1Manager instance;

	return &instance;
}


//------------------------------ Primary Functions

void manager::T1Manager::init(ModelManager* model_manager, UserInteractionManager* user_interaction_manager, CameraManager* camera_manager)
{
	this->model_manager = model_manager;
	this->user_interaction_manager = user_interaction_manager;
	this->camera_manager = camera_manager;

	this->operations = new tema1::Operations(model_manager, user_interaction_manager, camera_manager);

	this->point_picking_listener = new tema1::PointPickingListener(model_manager, user_interaction_manager, camera_manager, operations);
	this->drag_and_drop_listener = new tema1::DragAndDropListener(model_manager, user_interaction_manager, camera_manager, operations);
	this->curves_and_surfaces = new tema1::CurvesAndSurfaces(model_manager, user_interaction_manager, camera_manager);
}





void manager::T1Manager::listener()
{
	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_R))
	{
		this->model_manager->clean();
		this->curves_and_surfaces->clean();

		this->isPointPicked = false;
		this->isAxisPicked = false;
		this->isEditMode = false;

		this->curves_and_surfaces->axis_model->meshes[0]->vertices[0] = vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2());
		this->curves_and_surfaces->axis_model->meshes[0]->vertices[1] = vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2());
		this->curves_and_surfaces->axis_model->meshes[0]->vertices[2] = vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2());
		this->curves_and_surfaces->axis_model->meshes[0]->vertices[3] = vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2());

		this->curves_and_surfaces->resendModelToManager(this->curves_and_surfaces->axis_model);

		std::cout << "Creative Mode Activated\n";
	}

	if (isEditMode)
	{
		if (this->user_interaction_manager->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			model::ModelFormat* model;
			GLuint mesh_idx;
			GLuint vertex_idx;

			if (this->point_picking_listener->isPointPicked(this->curves_and_surfaces->getModels(), model, mesh_idx, vertex_idx))
			{
				this->drag_and_drop_listener->setPointToProcess(model, mesh_idx, vertex_idx, this->user_interaction_manager->getMouseCursorPosition());

				glm::vec3 point = model->meshes[mesh_idx]->vertices[vertex_idx].position;

				this->curves_and_surfaces->axis_model->meshes[0]->vertices[0] = vertex::VertexFormat(point, glm::vec3(), glm::vec2());
				this->curves_and_surfaces->axis_model->meshes[0]->vertices[1] = vertex::VertexFormat(point + glm::vec3(0.2, 0.0, 0.0), glm::vec3(), glm::vec2());
				this->curves_and_surfaces->axis_model->meshes[0]->vertices[2] = vertex::VertexFormat(point + glm::vec3(0.0, 0.2, 0.0), glm::vec3(), glm::vec2());
				this->curves_and_surfaces->axis_model->meshes[0]->vertices[3] = vertex::VertexFormat(point + glm::vec3(0.0, 0.0, 0.2), glm::vec3(), glm::vec2());

				this->model_manager->update(this->curves_and_surfaces->axis_model);

				this->isPointPicked = true;
			}
		}

		if (!this->isAxisPicked && this->isPointPicked && this->user_interaction_manager->isMouseButtonActive(GLFW_MOUSE_BUTTON_1))
		{
			GLuint axis_picked = this->point_picking_listener->isAxisPicked(this->curves_and_surfaces->axis_model);

			if (axis_picked > 0)
			{
				this->isAxisPicked = true;
				this->drag_and_drop_listener->setAxisToProcess(axis_picked, this->curves_and_surfaces->axis_model);
				this->last_mouse_pos = this->operations->getMousePosInWorldCoord(0.95f);
			}
		}

		if (this->isAxisPicked && this->user_interaction_manager->isMouseButtonActive(GLFW_MOUSE_BUTTON_1))
		{
			this->current_mouse_pos = this->operations->getMousePosInWorldCoord(0.95f);

			this->drag_and_drop_listener->listener(this->current_mouse_pos - this->last_mouse_pos);

			this->curves_and_surfaces->resendModelToManager(this->drag_and_drop_listener->model);
			this->curves_and_surfaces->resendModelToManager(this->curves_and_surfaces->axis_model);

			this->last_mouse_pos = this->current_mouse_pos;
		}

		if (this->isAxisPicked && !this->user_interaction_manager->isMouseButtonActive(GLFW_MOUSE_BUTTON_1))
		{
			this->isAxisPicked = false;
			this->drag_and_drop_listener->setAxisToProcess(0, nullptr);
		}
	}


	if (!this->isEditMode && this->user_interaction_manager->isKeyPressed(GLFW_KEY_E))
	{
		this->isEditMode = this->curves_and_surfaces->canActivateEditing();

		if (this->isEditMode)
			std::cout << "Edit Mode Activated\n";

	}

	if (this->isEditMode && this->user_interaction_manager->isKeyPressed(GLFW_KEY_C))
	{
		this->curves_and_surfaces->axis_model->meshes[0]->vertices[0] = vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2());
		this->curves_and_surfaces->axis_model->meshes[0]->vertices[1] = vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2());
		this->curves_and_surfaces->axis_model->meshes[0]->vertices[2] = vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2());
		this->curves_and_surfaces->axis_model->meshes[0]->vertices[3] = vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2());

		this->curves_and_surfaces->resendModelToManager(this->curves_and_surfaces->axis_model);

		this->isPointPicked = false;

		this->isEditMode = false;
		std::cout << "Creative Mode Activated\n";
		return;
	}

	if (isEditMode)
		return;

	this->isExistingModelPicked = false;

	if (!this->curves_and_surfaces->isModelUnderProcessing() && this->user_interaction_manager->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		model::ModelFormat* model;
		GLuint mesh_idx;
		GLuint vertex_idx;

		if (this->point_picking_listener->isPointPicked(this->curves_and_surfaces->getModels(), model, mesh_idx, vertex_idx))
		{
			this->curves_and_surfaces->setCurrentModel(model);
			this->isExistingModelPicked = true;
		}
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_0))
	{
		std::cout << "Curve set to NONE\n";
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_1))
	{
		this->curves_and_surfaces->startNewModelProcessing(model::CurveType::HERMITE);

		std::cout << "Curve set to HERMITE\n";
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_2))
	{
		this->curves_and_surfaces->startNewModelProcessing(model::CurveType::BEZIER);

		std::cout << "Curve set to BEZIER\n";
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_3))
	{
		this->curves_and_surfaces->startNewModelProcessing(model::CurveType::BSPLINE);

		std::cout << "Curve set to B-SPLINE\n";
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_4))
	{
		this->curves_and_surfaces->startNewModelProcessing(model::CurveType::SPLINE);

		std::cout << "Curve set to SPLINE\n";
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_5))
	{
		this->curves_and_surfaces->startNewModelProcessing(model::CurveType::NURBS);

		std::cout << "Curve set to NURBS\n";
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_6))
	{
		this->curves_and_surfaces->startNewModelProcessing(model::CurveType::S_BEZIER);

		std::cout << "Surface set to BEZIER\n";
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_7))
	{
		this->curves_and_surfaces->startNewModelProcessing(model::CurveType::S_SPLINE);

		std::cout << "Surface set to SPLINE\n";
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_8))
	{
		this->curves_and_surfaces->startNewModelProcessing(model::CurveType::S_NURBS);

		std::cout << "Surface set to NURB\n";
	}

	if (!this->isExistingModelPicked && this->user_interaction_manager->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		glm::vec3 point = this->operations->getMousePosInWorldCoord(0.95f);

		this->curves_and_surfaces->insertPoint(point);
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_F))
	{
		this->curves_and_surfaces->endModelProcessing();
	}

	if (static_cast<GLint>(userinteraction::Mouse::getScrollOffset().y) != 0)
	{
		this->curves_and_surfaces->updateCurvePointsNo(static_cast<GLint>(userinteraction::Mouse::getScrollOffset().y));
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_RIGHT) || userinteraction::Keyboard::getKeysAction()[GLFW_KEY_RIGHT] == GLFW_REPEAT)
	{
		this->curves_and_surfaces->increaseCurvesNo();
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_LEFT) || userinteraction::Keyboard::getKeysAction()[GLFW_KEY_LEFT] == GLFW_REPEAT)
	{
		this->curves_and_surfaces->decreaseCurvesNo();
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_Z))
	{
		this->curves_and_surfaces->setModelTransformation(0);
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_X))
	{
		this->curves_and_surfaces->setModelTransformation(1);
	}

	if (this->user_interaction_manager->isKeyPressed(GLFW_KEY_I))
	{
		this->curves_and_surfaces->printCurrentModelInfo();
	}
}

