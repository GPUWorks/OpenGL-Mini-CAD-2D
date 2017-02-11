#include "CameraRotation.h"





//------------------------------ Constructors

camera::CameraRotation::CameraRotation()
{

}


//------------------------------ Primary Functions

glm::mat4 camera::CameraRotation::getViewRotationMatrix()
{
	glm::quat orientation = this->getPitchAngleRotationQuaternion() * this->getYawAngleRotationQuaternion();
	orientation = glm::normalize(orientation);

	return glm::mat4_cast(orientation);
}


//------------------------------ Secondary Functions (Provide Data)

void camera::CameraRotation::updateYawAngle(GLfloat yaw_angle_degrees)
{
	this->yaw_angle_degrees += yaw_angle_degrees;
}

void camera::CameraRotation::updatePitchAngle(GLfloat pitch_angle_degrees)
{
	this->pitch_angle_degrees += pitch_angle_degrees;
}


//------------------------------ Secondary Functions (Retrieve Data)

glm::quat camera::CameraRotation::getYawAngleRotationQuaternion()
{
	return glm::angleAxis(glm::radians(this->yaw_angle_degrees), glm::vec3(0, 1, 0));
}

glm::quat camera::CameraRotation::getPitchAngleRotationQuaternion()
{
	return glm::angleAxis(glm::radians(this->pitch_angle_degrees), glm::vec3(1, 0, 0));
}

