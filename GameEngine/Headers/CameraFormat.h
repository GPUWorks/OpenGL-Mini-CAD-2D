#pragma once

#include "defcs.h"




///	<summary>
///		Contains classes used for creating and manipulating engine cameras
///	</summary>
namespace camera
{
	class CameraFormat
	{
	protected:
		glm::vec3 position;

		GLfloat fovy;

		GLfloat aspect_ratio;

		GLfloat znear;

		GLfloat zfar;

		glm::mat4 view_matrix;

		glm::mat4 perspective_projection_matrix;

		glm::mat4 orthographic_projection_matrix;


	public:
		void updateViewMatrix(glm::mat4 view_rotation_matrix, glm::mat4 view_translation_matrix);

		void updatePerspectiveProjectionMatrix();

		void updateOrthographicProjectionMatrix();

		glm::mat4 getViewMatrix();

		glm::mat4 getPerspectiveProjectionMatrix();

		glm::mat4 getOrthographicProjectionMatrix();
		
		glm::vec3 getRightVector();

		glm::vec3 getDirectionVector();

		glm::vec3 getUpVector();
	};
}