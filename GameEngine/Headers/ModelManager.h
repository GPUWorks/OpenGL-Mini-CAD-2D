#pragma once

#include "defcs.h"

#include <map>
#include <string>
#include <fstream>

#include "ModelLoader.h"

#include "ModelFormat.h"
#include "ShaderFormat.h"
#include "CameraFormat.h"

#include "StorageManager.h"


namespace manager
{
	class ModelManager
	{
	private:
		std::map<GLuint, model::ModelFormat*> models;
		manager::StorageManager* storage_manager;
		std::string exec_path;

		//------------------------------ Constructors
		ModelManager() {};


	public:
		//------------------------------ Singleton Pattern
		ModelManager(const ModelManager &) = delete;
		const ModelManager &operator=(const ModelManager &) = delete;
		static ModelManager* getInstance();

		//------------------------------ Primary Functions
		void init(std::string exec_path, manager::StorageManager* storage_manager);
		void listener();

		//------------------------------ Secondary Functions (Provide Data)
		void add(GLuint model_id, std::string file_directory, std::string file_name);
		void add(model::ModelFormat* model);
		void update(model::ModelFormat* model);
		void clean();


		void processModelsInfoFile(std::string file_path);
	};
}