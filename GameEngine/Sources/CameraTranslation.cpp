#include "CameraTranslation.h"




//------------------------------ Constructors

camera::CameraTranslation::CameraTranslation()
{

}


//------------------------------ Primary Functions

glm::mat4 camera::CameraTranslation::getViewTranslationMatrix(glm::vec3* camera_position, const glm::mat4 view_matrix)
{
	glm::mat4 translate = glm::mat4(1.0f);
	*camera_position += getXAxisTranslationVector(view_matrix) + getZAxisTranslationVector(view_matrix);

	return glm::translate(translate, -(*camera_position));
}


//------------------------------ Secondary Functions

void camera::CameraTranslation::updateXAxisTranslationStep(GLenum orientation, GLfloat translation_increase)
{
	switch (orientation) {
	case ENG_CAMERA_ORIENTATION_POSITIVE_AXIS: {
		this->x_translation_step += frame::FrameFormat::getDeltaTime() * translation_increase;
		break;
	}
	case ENG_CAMERA_ORIENTATION_NEGATIVE_AXIS: {
		this->x_translation_step -= frame::FrameFormat::getDeltaTime() * translation_increase;
		break;
	}
	}
}

void camera::CameraTranslation::updateZAxisTranslationStep(GLenum orientation, GLfloat translation_increase)
{
	switch (orientation) {
	case ENG_CAMERA_ORIENTATION_POSITIVE_AXIS: {
		this->z_translation_step += frame::FrameFormat::getDeltaTime() * translation_increase;
		break;
	}
	case ENG_CAMERA_ORIENTATION_NEGATIVE_AXIS: {
		this->z_translation_step -= frame::FrameFormat::getDeltaTime() * translation_increase;
		break;
	}
	}
}

void camera::CameraTranslation::resetXAxisTranslationStep()
{
	this->x_translation_step = 0.0f;
}

void camera::CameraTranslation::resetZAxisTranslationStep()
{
	this->z_translation_step = 0.0f;
}



//------------------------------ Secondary Functions (Retrieve Data)

glm::vec3 camera::CameraTranslation::getXAxisTranslationVector(const glm::mat4 view_matrix)
{
	glm::vec3 right(view_matrix[0][0], view_matrix[1][0], view_matrix[2][0]);

	return right * static_cast<GLfloat>(this->x_translation_step);
}

glm::vec3 camera::CameraTranslation::getZAxisTranslationVector(const glm::mat4 view_matrix)
{
	glm::vec3 direction(view_matrix[0][2], view_matrix[1][2], view_matrix[2][2]);

	return direction * static_cast<GLfloat>(this->z_translation_step);
}