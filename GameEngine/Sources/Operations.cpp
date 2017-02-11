#include "Operations.h"



namespace tema1
{
	Operations::Operations(manager::ModelManager* model_manager, manager::UserInteractionManager* user_interaction_manager, manager::CameraManager* camera_manager)
	{
		this->model_manager = model_manager;
		this->user_interaction_manager = user_interaction_manager;
		this->camera_manager = camera_manager;
	}


	glm::vec3 Operations::getMousePosInWorldCoord(float z)
	{
		glm::vec3 win_coord = glm::vec3((double)this->user_interaction_manager->getMouseCursorPosition().x, (double)this->user_interaction_manager->getMouseCursorPosition().y, z);

		glm::mat4 view = this->camera_manager->getPlayerCamera()->getViewMatrix();
		glm::mat4 proj = this->camera_manager->getPlayerCamera()->getPerspectiveProjectionMatrix();

		win_coord.y = 600 - win_coord.y;

		return glm::unProject(win_coord, view, proj, glm::vec4(0, 0, 800, 600));
	}
}