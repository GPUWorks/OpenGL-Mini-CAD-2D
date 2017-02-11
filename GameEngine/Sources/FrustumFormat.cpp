#include "FrustumFormat.h"




camera::FrustumFormat::FrustumFormat()
{

}

void camera::FrustumFormat::updateFrustumPlanesData(GLfloat fovy, GLfloat aspect_ratio, GLfloat znear, GLfloat zfar)
{
	this->znear_height = 2.0f * tanf(fovy / 2.0f) * znear;
	this->znear_width = this->znear_height * aspect_ratio;

	this->zfar_height = 2.0f * tanf(fovy / 2.0f) * zfar;
	this->zfar_width = this->zfar_height * aspect_ratio;
}