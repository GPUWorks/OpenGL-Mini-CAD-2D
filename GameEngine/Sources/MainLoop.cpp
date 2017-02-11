#include "MainLoop.h"


//------------------------------ Constructors

MainLoop::MainLoop(int argc, char** argv)
{
	this->exec_dir = getExecutableDirectory(argc, argv);

	this->glfw = new GLFW_Init(4, 3);
	this->glew = new GLEW_Init(GL_TRUE);

	this->instantiateManagers();
	this->initiateManagers();

	this->start();
}


//------------------------------ Primary Functions

void MainLoop::start()
{
	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	while (!glfwWindowShouldClose(window_manager->getPrimaryWindowGLFW()))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		frame_manager->listener();
		storage_manager->listener();
		camera_manager->listener(window_manager->getPrimaryWindowGLFW());
		draw_manager->listener();

		t1_manager->listener();

		user_interaction_manager->listener();

		glfwSwapBuffers(window_manager->getPrimaryWindowGLFW());
	}

	glfwTerminate();
}

void MainLoop::instantiateManagers()
{
	window_manager = WindowManager::getInstance();
	frame_manager = FrameManager::getInstance();
	user_interaction_manager = UserInteractionManager::getInstance();
	shader_manager = ShaderManager::getInstance();
	camera_manager = CameraManager::getInstance();
	model_manager = ModelManager::getInstance();
	storage_manager = StorageManager::getInstance();
	draw_manager = DrawManager::getInstance();

	t1_manager = T1Manager::getInstance();
}


void MainLoop::initiateManagers()
{
	window_manager->init(this->glfw, this->glew);
	frame_manager->init();
	user_interaction_manager->init(window_manager->getPrimaryWindow());

	shader_manager->init(exec_dir);
	camera_manager->init(window_manager->getPrimaryWindowGLFW());
	storage_manager->init();
	model_manager->init(exec_dir, storage_manager);

	draw_manager->init(storage_manager, shader_manager, camera_manager);

	t1_manager->init(model_manager, user_interaction_manager, camera_manager);
}


std::string MainLoop::getExecutableDirectory(int argc, char** argv)
{
	std::string exec_str(argv[0]);
	GLuint last_slash = exec_str.find_last_of(PATH_SEPARATOR);

	return exec_str.substr(0, last_slash + 1);
}