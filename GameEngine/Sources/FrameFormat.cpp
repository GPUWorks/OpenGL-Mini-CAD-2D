#include "FrameFormat.h"
#include <iostream>



GLdouble frame::FrameFormat::delta_time = 0.0f;
GLdouble frame::FrameFormat::last_time = 0.0f;
GLuint frame::FrameFormat::fps_counter = 0;
GLdouble frame::FrameFormat::total_time_passed = glfwGetTime();



//------------------------------ Primary Functions

void frame::FrameFormat::computeDeltaTime()
{
	// Calculate deltatime of current frame
	GLdouble current_time = glfwGetTime();

	FrameFormat::delta_time = current_time - FrameFormat::last_time;
	FrameFormat::last_time = current_time;
}

void frame::FrameFormat::computeAndDisplayFpsToConsole()
{
	FrameFormat::fps_counter++;

	if (glfwGetTime() - FrameFormat::total_time_passed >= 1.0f) {
		std::cout << "\r\r" << FrameFormat::fps_counter;
		FrameFormat::fps_counter = 0;
		FrameFormat::total_time_passed += 1.0f;
	}
}


//------------------------------ Secondary Functions (Retrieve Data)
GLdouble frame::FrameFormat::getDeltaTime()
{
	return FrameFormat::delta_time;
}