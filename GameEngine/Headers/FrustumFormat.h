#pragma once

#include "defcs.h"




///	<summary>
///		Contains classes used for creating and manipulating engine cameras
///	</summary>
namespace camera
{
	///	<summary> Contains general data about view frustum </summary>
	class FrustumFormat
	{
	private:
		///	<summary> Near frustum plane width </summary>
		GLfloat znear_width;

		///	<summary> Near frustum plane height </summary>
		GLfloat znear_height;

		///	<summary> Far frustum plane width </summary>
		GLfloat zfar_width;

		///	<summary> Far frustum plane height </summary>
		GLfloat zfar_height;

	public:
		/// <summary> Default Constructor. Does nothing </summary>
		FrustumFormat();

		/// <summary> Compute near and far planes width and length </summary>
		void updateFrustumPlanesData(GLfloat fovy, GLfloat aspect_ratio, GLfloat znear, GLfloat zfar);
	};
}