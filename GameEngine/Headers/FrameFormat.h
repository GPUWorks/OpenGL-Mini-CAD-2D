#pragma once

#include "defcs.h"



///	<summary>
///		Contains classes used for display frames managment
///	</summary>
namespace frame
{
	///	<summary> Acts like a listener for display frames </summary>
	///	<remarks> This class generates and displays fps </remarks>
	class FrameFormat
	{
		///	<summary> Time between current frame and last frame </summary>
		static GLdouble delta_time;

		///	<summary> Time of the last frame </summary>
		static GLdouble last_time;

		///	<summary> Time passed since the Engine was started </summary>
		static GLdouble total_time_passed;

		///	<summary> Gives the number of frames per second <summary>
		static GLuint fps_counter;

		
	public:
		///	<summary> Compute the time between current frame and last frame </summary>
		static void computeDeltaTime();

		///	<summary> Compute fps and display it to console </summary>
		static void computeAndDisplayFpsToConsole();

		///	<summary> Retrieve the time between current frame and last frame </summary>
		/// <returns> Time between two consecutive frames </returns>
		static GLdouble getDeltaTime();
	};
}