#include "DragAndDropListener.h"



namespace tema1
{
	DragAndDropListener::DragAndDropListener(manager::ModelManager* model_manager, manager::UserInteractionManager* user_interaction_manager, manager::CameraManager* camera_manager, Operations* operations)
	{
		this->model_manager = model_manager;
		this->user_interaction_manager = user_interaction_manager;
		this->camera_manager = camera_manager;
		this->operations = operations;
	}

	void DragAndDropListener::setPointToProcess(model::ModelFormat* model, GLuint mesh_idx, GLuint vertex_idx, glm::vec2 cursor_position)
	{
		this->model = model;
		this->mesh_idx = mesh_idx;
		this->vertex_idx = vertex_idx;
	}

	void DragAndDropListener::setAxisToProcess(GLuint axis, model::ModelFormat* axisModel)
	{
		this->axis = axis;
		this->axisModel = axisModel;
	}

	void DragAndDropListener::listener(glm::vec3 mouse_position)
	{
		if (this->axis == 1)
			mouse_position = glm::vec3(mouse_position.x, 0.0f, 0.0f);
		
		if (this->axis == 2)
			mouse_position = glm::vec3(0.0f, mouse_position.y, 0.0f);

		if (this->axis == 3)
			mouse_position = glm::vec3(0.0f, 0.0f, mouse_position.z);

		if (this->model != nullptr && this->axisModel != nullptr)
		{
			switch (model->ctype)
			{
			case model::BEZIER:
			{
				model->meshes[this->mesh_idx]->vertices[this->vertex_idx].position += mouse_position;

				if (this->vertex_idx == 3 && this->mesh_idx + 1 <= model->meshes.size() - 1)
				{
					model->meshes[this->mesh_idx + 1]->vertices[0].position += mouse_position;
				}
				else if (this->vertex_idx == 0 && this->mesh_idx > 0)
				{
					model->meshes[this->mesh_idx - 1]->vertices[3].position += mouse_position;
				}

				break;
			}

			case model::HERMITE:
			{
				model->meshes[this->mesh_idx]->vertices[this->vertex_idx].position += mouse_position;

				if (this->vertex_idx == 2 && this->mesh_idx + 1 <= model->meshes.size() - 1)
				{
					model->meshes[this->mesh_idx + 1]->vertices[0].position += mouse_position;
				}
				else if (this->vertex_idx == 1 && this->mesh_idx > 0)
				{
					model->meshes[this->mesh_idx - 1]->vertices[3].position += mouse_position;
				}
				else if (this->vertex_idx == 3 && this->mesh_idx + 1 <= model->meshes.size() - 1)
				{
					model->meshes[this->mesh_idx + 1]->vertices[1].position += mouse_position;
				}
				else if (this->vertex_idx == 0 && this->mesh_idx > 0)
				{
					model->meshes[this->mesh_idx - 1]->vertices[2].position += mouse_position;
				}

				break;
			}

			case model::BSPLINE:
			{
				model->meshes[this->mesh_idx]->vertices[this->vertex_idx].position += mouse_position;

				if (this->vertex_idx == 2 && this->mesh_idx + 1 <= model->meshes.size() - 1)
				{
					model->meshes[this->mesh_idx + 1]->vertices[1].position += mouse_position;
				}

				if (this->vertex_idx == 2 && this->mesh_idx + 2 <= model->meshes.size() - 1)
				{
					model->meshes[this->mesh_idx + 2]->vertices[0].position += mouse_position;
				}

				if (this->vertex_idx == 0 && this->mesh_idx > 0)
				{
					model->meshes[this->mesh_idx - 1]->vertices[1].position += mouse_position;
				}

				if (this->vertex_idx == 0 && this->mesh_idx > 1)
				{
					model->meshes[this->mesh_idx - 2]->vertices[2].position += mouse_position;
				}


				if (this->vertex_idx == 1 && this->mesh_idx + 1 <= model->meshes.size() - 1)
				{
					model->meshes[this->mesh_idx + 1]->vertices[0].position += mouse_position;
				}

				if (this->vertex_idx == 1 && this->mesh_idx > 0)
				{
					model->meshes[this->mesh_idx - 1]->vertices[2].position += mouse_position;
				}

				break;
			}

			case model::NURBS:
			{
				model->meshes[this->mesh_idx]->vertices[this->vertex_idx].position += mouse_position;

				if (this->vertex_idx == 2 && this->mesh_idx + 1 <= model->meshes.size() - 1)
				{
					model->meshes[this->mesh_idx + 1]->vertices[1].position += mouse_position;
				}

				if (this->vertex_idx == 2 && this->mesh_idx + 2 <= model->meshes.size() - 1)
				{
					model->meshes[this->mesh_idx + 2]->vertices[0].position += mouse_position;
				}

				if (this->vertex_idx == 0 && this->mesh_idx > 0)
				{
					model->meshes[this->mesh_idx - 1]->vertices[1].position += mouse_position;
				}

				if (this->vertex_idx == 0 && this->mesh_idx > 1)
				{
					model->meshes[this->mesh_idx - 2]->vertices[2].position += mouse_position;
				}


				if (this->vertex_idx == 1 && this->mesh_idx + 1 <= model->meshes.size() - 1)
				{
					model->meshes[this->mesh_idx + 1]->vertices[0].position += mouse_position;
				}

				if (this->vertex_idx == 1 && this->mesh_idx > 0)
				{
					model->meshes[this->mesh_idx - 1]->vertices[2].position += mouse_position;
				}

				break;
			}

			case model::SPLINE:
			{
				if (this->vertex_idx > 1)
					break;

				model->meshes[this->mesh_idx]->vertices[this->vertex_idx].position += mouse_position;

				if (this->mesh_idx == 0 && model->meshes.size() > 0)
				{
					model->meshes[this->mesh_idx]->vertices[2] = vertex::VertexFormat(model->meshes[this->mesh_idx]->vertices[1].position - model->meshes[this->mesh_idx]->vertices[0].position, glm::vec3(), glm::vec2());
				

					if (model->meshes.size() > 1)
					{
						if (this->vertex_idx == 1)
							model->meshes[this->mesh_idx + 1]->vertices[0].position += mouse_position;

						model->meshes[this->mesh_idx]->vertices[3] = vertex::VertexFormat(model->meshes[this->mesh_idx + 1]->vertices[1].position - model->meshes[this->mesh_idx]->vertices[0].position, glm::vec3(), glm::vec2());
						model->meshes[this->mesh_idx + 1]->vertices[2] = vertex::VertexFormat(model->meshes[this->mesh_idx + 1]->vertices[1].position - model->meshes[this->mesh_idx]->vertices[0].position, glm::vec3(), glm::vec2());
					}
					else
						model->meshes[this->mesh_idx]->vertices[3] = vertex::VertexFormat(model->meshes[this->mesh_idx]->vertices[1].position - model->meshes[this->mesh_idx]->vertices[0].position, glm::vec3(), glm::vec2());
				}

				if (this->mesh_idx > 0 && this->mesh_idx < model->meshes.size() - 1)
				{
					if (this->vertex_idx == 0)
					{
						model->meshes[this->mesh_idx - 1]->vertices[1].position += mouse_position;

						model->meshes[this->mesh_idx]->vertices[2] = vertex::VertexFormat(model->meshes[this->mesh_idx]->vertices[1].position - model->meshes[this->mesh_idx - 1]->vertices[0].position, glm::vec3(), glm::vec2());
						model->meshes[this->mesh_idx - 1]->vertices[3] = vertex::VertexFormat(model->meshes[this->mesh_idx]->vertices[1].position - model->meshes[this->mesh_idx - 1]->vertices[0].position, glm::vec3(), glm::vec2());
					}

					if (this->vertex_idx == 1)
					{
						model->meshes[this->mesh_idx + 1]->vertices[0].position += mouse_position;

						model->meshes[this->mesh_idx]->vertices[3] = vertex::VertexFormat(model->meshes[this->mesh_idx + 1]->vertices[1].position - model->meshes[this->mesh_idx]->vertices[0].position, glm::vec3(), glm::vec2());
						model->meshes[this->mesh_idx + 1]->vertices[2] = vertex::VertexFormat(model->meshes[this->mesh_idx + 1]->vertices[1].position - model->meshes[this->mesh_idx]->vertices[0].position, glm::vec3(), glm::vec2());
					}
				}

				if (this->mesh_idx == model->meshes.size() - 1 && this->mesh_idx != 0)
				{
					model->meshes[this->mesh_idx]->vertices[3] = vertex::VertexFormat(model->meshes[this->mesh_idx]->vertices[1].position - model->meshes[this->mesh_idx]->vertices[0].position, glm::vec3(), glm::vec2());

					if (this->vertex_idx == 0)
						model->meshes[this->mesh_idx - 1]->vertices[1].position += mouse_position;

					model->meshes[this->mesh_idx]->vertices[2] = vertex::VertexFormat(model->meshes[this->mesh_idx]->vertices[1].position - model->meshes[this->mesh_idx - 1]->vertices[0].position, glm::vec3(), glm::vec2());
					model->meshes[this->mesh_idx - 1]->vertices[3] = vertex::VertexFormat(model->meshes[this->mesh_idx]->vertices[1].position - model->meshes[this->mesh_idx - 1]->vertices[0].position, glm::vec3(), glm::vec2());
				}

				break;
			}

			case model::S_NURBS:
			{
				model->meshes[this->mesh_idx]->vertices[this->vertex_idx].position += mouse_position;

				break;
			}

			case model::S_SPLINE:
			{
				model->meshes[this->mesh_idx]->vertices[this->vertex_idx].position += mouse_position;

				break;
			}

			case model::S_BEZIER:
			{
				model->meshes[this->mesh_idx]->vertices[this->vertex_idx].position += mouse_position;

				break;
			}

			}

			model::ModelFormat* axis = this->axisModel;
			axis->meshes[0]->vertices[0] = vertex::VertexFormat(this->model->meshes[mesh_idx]->vertices[vertex_idx].position, glm::vec3(), glm::vec2());
			axis->meshes[0]->vertices[1] = vertex::VertexFormat(this->model->meshes[mesh_idx]->vertices[vertex_idx].position + glm::vec3(0.2, 0.0, 0.0), glm::vec3(), glm::vec2());
			axis->meshes[0]->vertices[2] = vertex::VertexFormat(this->model->meshes[mesh_idx]->vertices[vertex_idx].position + glm::vec3(0.0, 0.2, 0.0), glm::vec3(), glm::vec2());
			axis->meshes[0]->vertices[3] = vertex::VertexFormat(this->model->meshes[mesh_idx]->vertices[vertex_idx].position + glm::vec3(0.0, 0.0, 0.2), glm::vec3(), glm::vec2());
		}

	}

	void DragAndDropListener::reset()
	{
		this->model = nullptr;
	}
}