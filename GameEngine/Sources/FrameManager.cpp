#include "FrameManager.h"



//------------------------------ Singleton Pattern

manager::FrameManager* manager::FrameManager::getInstance()
{
	static FrameManager instance;

	return &instance;
}


//------------------------------ Primary Functions

void manager::FrameManager::init()
{

}

void manager::FrameManager::listener()
{
	frame::FrameFormat::computeDeltaTime();
	frame::FrameFormat::computeAndDisplayFpsToConsole();
}