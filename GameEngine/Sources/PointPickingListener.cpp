#include "PointPickingListener.h"



namespace tema1
{
	PointPickingListener::PointPickingListener(manager::ModelManager* model_manager, manager::UserInteractionManager* user_interaction_manager, manager::CameraManager* camera_manager, Operations* operations)
	{
		this->model_manager = model_manager;
		this->user_interaction_manager = user_interaction_manager;
		this->camera_manager = camera_manager;
		this->operations = operations;
	}


	float PointPickingListener::getPointLineDistance3D(glm::vec3 p, glm::vec3 lp1, glm::vec3 lp2)
	{
		glm::vec3 vector_p_to_lp2 = lp2 - p;
		float distance = sqrtf(vector_p_to_lp2.x * vector_p_to_lp2.x + vector_p_to_lp2.y * vector_p_to_lp2.y + vector_p_to_lp2.z * vector_p_to_lp2.z);

		glm::vec3 vector_lp1_to_lp2 = glm::normalize(lp2 - lp1);
		glm::vec3 cross_product = glm::cross(vector_p_to_lp2, vector_lp1_to_lp2);

		float magnitude = sqrtf(cross_product.x * cross_product.x + cross_product.y * cross_product.y + cross_product.z * cross_product.z);

		return magnitude;
	}

	bool PointPickingListener::isPointPicked(std::map<model::CurveType, std::vector<model::ModelFormat*>>& models, model::ModelFormat* &model, GLuint &mesh_idx, GLuint &vertex_idx)
	{
		glm::vec3 start = operations->getMousePosInWorldCoord(0.0f);
		glm::vec3 end = operations->getMousePosInWorldCoord(1.0f);

		typedef std::map<model::CurveType, std::vector<model::ModelFormat*>>::iterator it_type;
		for (it_type iterator = models.begin(); iterator != models.end(); iterator++) {
			for (model::ModelFormat* m : iterator->second)
			{
				for (GLuint i = 0; i < m->meshes.size(); i++)
				{
					for (GLuint j = 0; j < m->meshes[i]->vertices.size(); j++)
					{
						if (getPointLineDistance3D(m->meshes[i]->vertices[j].position, start, end) < 0.01f)
						{
							model = m;
							mesh_idx = i;
							vertex_idx = j;

							return true;
						}
					}
				}
			}
		}

		return false;
	}

	bool PointPickingListener::isAxisPointPicked(glm::vec3 from, glm::vec3 to)
	{
		glm::vec3 start = operations->getMousePosInWorldCoord(0.0f);
		glm::vec3 end = operations->getMousePosInWorldCoord(1.0f);

		glm::vec3 offset = (to - from) / glm::vec3(100.0f, 100.0f, 100.0f);

		for (float i = 0.0; i < 101.0; i++)
		{
			if (getPointLineDistance3D(from + glm::vec3(i, i, i) * offset, start, end) < 0.005f)
			{
				return true;
			}
		}

		return false;
	}

	GLuint PointPickingListener::isAxisPicked(model::ModelFormat* model)
	{
		glm::vec3 center = model->meshes.back()->vertices[0].position;
		glm::vec3 x = model->meshes.back()->vertices[1].position;
		glm::vec3 y = model->meshes.back()->vertices[2].position;
		glm::vec3 z = model->meshes.back()->vertices[3].position;

		if (isAxisPointPicked(center, x))
			return 1;
		else if (isAxisPointPicked(center, y))
			return 2;
		else if (isAxisPointPicked(center, z))
			return 3;

		return 0;
	}
}