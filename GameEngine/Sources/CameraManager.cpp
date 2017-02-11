#include "CameraManager.h"



//------------------------------ Singleton Pattern

manager::CameraManager* manager::CameraManager::getInstance()
{
	static CameraManager instance;

	return &instance;
}


//------------------------------ Primary Functions

void manager::CameraManager::init(GLFWwindow* window)
{
	int width, height;

	glfwGetWindowSize(window, &width, &height);

	glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 3.0f);

	GLfloat fovy = glm::radians(45.0f);
	GLfloat aspect_ratio = (GLfloat) width / (GLfloat) height;
	GLfloat znear = 0.1f;
	GLfloat zfar = 100.0f;

	setPlayerCamera(new player::PlayerCamera(camera_position, fovy, aspect_ratio, znear, zfar));
}

void manager::CameraManager::listener(GLFWwindow* window)
{
	this->playerCameraListener(window);
}

void manager::CameraManager::playerCameraListener(GLFWwindow* window)
{
	this->player_camera->cameraListener(window);
}


//------------------------------ Secondary Functions (Provide Data)

void manager::CameraManager::setPlayerCamera(player::PlayerCamera* player_camera)
{
	this->player_camera = player_camera;
}

void manager::CameraManager::setPlayerCameraUniforms(GLuint program)
{
	GLint vm_location = glGetUniformLocation(program, "view");
	GLint pm_location = glGetUniformLocation(program, "projection");

	GLint right_location = glGetUniformLocation(program, "right");
	GLint direction_location = glGetUniformLocation(program, "direction");
	GLint up_location = glGetUniformLocation(program, "up");

	// Pass the matrices to the shader
	glUniformMatrix4fv(vm_location, 1, GL_FALSE, glm::value_ptr(this->player_camera->getViewMatrix()));
	glUniformMatrix4fv(pm_location, 1, GL_FALSE, glm::value_ptr(this->player_camera->getPerspectiveProjectionMatrix()));

	glUniform3f(right_location, this->player_camera->getRightVector().x, this->player_camera->getRightVector().y, this->player_camera->getRightVector().z);
	glUniform3f(direction_location, this->player_camera->getDirectionVector().x, this->player_camera->getDirectionVector().y, this->player_camera->getDirectionVector().z);
	glUniform3f(up_location, this->player_camera->getUpVector().x, this->player_camera->getUpVector().y, this->player_camera->getUpVector().z);
}


//------------------------------ Secondary Functions (Retrieve Data)

player::PlayerCamera* manager::CameraManager::getPlayerCamera()
{
	return this->player_camera;
}