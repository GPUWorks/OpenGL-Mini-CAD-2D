#include "CameraFormat.h"

#include <glm\gtc\matrix_transform.hpp>






//------------------------------ Primary Functions
void camera::CameraFormat::updateViewMatrix(glm::mat4 view_rotation_matrix, glm::mat4 view_translation_matrix)
{
	this->view_matrix = view_rotation_matrix * view_translation_matrix;
}

void camera::CameraFormat::updatePerspectiveProjectionMatrix()
{
	this->perspective_projection_matrix = glm::perspective(this->fovy, this->aspect_ratio, this->znear, this->zfar);
}

void camera::CameraFormat::updateOrthographicProjectionMatrix()
{
	this->orthographic_projection_matrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);
}


//------------------------------ Secondary Functions (Retrieve Data)

glm::mat4 camera::CameraFormat::getViewMatrix()
{
	return this->view_matrix;
}

glm::mat4 camera::CameraFormat::getPerspectiveProjectionMatrix()
{
	return this->perspective_projection_matrix;
}

glm::mat4 camera::CameraFormat::getOrthographicProjectionMatrix()
{
	return this->orthographic_projection_matrix;
}

glm::vec3 camera::CameraFormat::getRightVector()
{
	return glm::normalize(glm::vec3(view_matrix[0][0], view_matrix[1][0], view_matrix[2][0]));
}

glm::vec3 camera::CameraFormat::getDirectionVector()
{
	return glm::normalize(glm::vec3(view_matrix[0][2], view_matrix[1][2], view_matrix[2][2]));
}

glm::vec3 camera::CameraFormat::getUpVector()
{
	return glm::normalize(glm::cross(getRightVector(), getDirectionVector()));
}