#pragma once

#include "defcs.h"

#include "FrameFormat.h"



///	<summary>
///		Contains classes used for creating and manipulating engine cameras
///	</summary>
namespace camera
{
	///	<summary> Contains data and methods used for camera translation </summary>
	class CameraTranslation
	{
	private:
		///	<summary> X axis camera translation </summary>
		GLdouble x_translation_step = 0.0f;

		///	<summary> Z axis camera translation </summary>
		GLdouble z_translation_step = 0.0f;

		/// <summary> Retrieve X axis translation vector </summary>
		/// <returns> A vector describing X axis translation </returns>
		glm::vec3 getXAxisTranslationVector(const glm::mat4 view_matrix);

		/// <summary> Retrieve Z axis translation vector </summary>
		/// <returns> A vector describing Z axis translation </returns>
		glm::vec3 getZAxisTranslationVector(const glm::mat4 view_matrix);

	protected:
		/// <summary> Default Constructor. Does nothing </summary>
		CameraTranslation();

		/// <summary> Retrieve translation matrix </summary>
		/// <returns> Translation matrix </returns>
		glm::mat4 getViewTranslationMatrix(glm::vec3* camera_position, const glm::mat4 view_matrix);

		/// <summary> Compute X axis translation </summary>
		void updateXAxisTranslationStep(GLenum orientation, GLfloat translation_increase);

		/// <summary> Compute Z axis translation </summary>
		void updateZAxisTranslationStep(GLenum orientation, GLfloat translation_increase);

		/// <summary> Set X axis translation to 0 </summary>
		void resetXAxisTranslationStep();

		/// <summary> Set Z axis translation to 0 </summary>
		void resetZAxisTranslationStep();
	};
}