#pragma once

#include "defcs.h"

#include "WindowManager.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "UserInteractionManager.h"
#include "ModelManager.h"
#include "FrameManager.h"
#include "StorageManager.h"
#include "DrawManager.h"

#include "Mouse.h"
#include "Keyboard.h"

#include "ShaderFormat.h"
#include "TextureLoader.h"

#include "T1Manager.h"



using namespace manager;


class MainLoop
{
private:
	GLFW_Init* glfw;
	GLEW_Init* glew;

	std::string exec_dir;

	// Managers declaration
	WindowManager* window_manager;
	FrameManager* frame_manager;
	UserInteractionManager* user_interaction_manager;

	ShaderManager* shader_manager;
	CameraManager* camera_manager;
	StorageManager* storage_manager;
	ModelManager* model_manager;

	DrawManager* draw_manager;

	T1Manager* t1_manager;


public:
	//------------------------------ Constructors
	MainLoop(int argc, char** argv);

	//------------------------------ Primary Functions
	void start();

	void instantiateManagers();
	void initiateManagers();

	std::string getExecutableDirectory(int argc, char** argv);
};