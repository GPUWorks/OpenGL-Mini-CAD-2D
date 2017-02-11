#pragma once

#include "defcs.h"



///	<summary>
///		Contains classes used for creating and manipulating engine cameras
///	</summary>
namespace camera
{
	///	<summary> Contains data and methods used for camera rotation </summary>
	class CameraRotation
	{
	private:
		///	<summary> Y axis camera rotation </summary>
		GLfloat yaw_angle_degrees = 0.0f;

		///	<summary> X axis camera rotation </summary>
		GLfloat pitch_angle_degrees = 0.0f;

		/// <summary> Retrieve yaw angle rotation as a quaternion </summary>
		/// <returns> Quaternion describing yaw rotation </returns>
		glm::quat getYawAngleRotationQuaternion();

		/// <summary> Retrieve pitch angle rotation as a quaternion </summary>
		/// <returns> Quaternion describing pitch rotation </returns>
		glm::quat getPitchAngleRotationQuaternion();

	protected:
		/// <summary> Default Constructor. Does nothing </summary>
		CameraRotation();

		/// <summary> Retrieve rotation matrix </summary>
		/// <returns> Rotation matrix </returns>
		glm::mat4 getViewRotationMatrix();

		/// <summary> Compute yaw angle </summary>
		void updateYawAngle(GLfloat yaw_angle_degrees);

		/// <summary> Compute pitch angle </summary>
		void updatePitchAngle(GLfloat pitch_angle_degrees);
	};
}