#include "ModelManager.h"




//------------------------------ Singleton Pattern

manager::ModelManager* manager::ModelManager::getInstance()
{
	static ModelManager instance;

	return &instance;
}


//------------------------------ Primary Functions

void manager::ModelManager::init(std::string exec_path, manager::StorageManager* storage_manager)
{
	this->exec_path = exec_path;
	this->storage_manager = storage_manager;

	this->processModelsInfoFile(exec_path + MODEL_MANAGER_STARTUP_INFO_FILE);
}

void manager::ModelManager::listener()
{

}


//------------------------------ Secondary Functions (Provide Data)

void manager::ModelManager::add(GLuint model_id, std::string file_directory, std::string file_name)
{
	model::ModelFormat* model = new model::ModelFormat();
	model->id = model_id;

	model::ModelLoader::loadModel(model, file_directory, file_name);

	this->models[model->id] = model;
	this->storage_manager->addModel(model);
}

void manager::ModelManager::update(model::ModelFormat* model)
{
	this->storage_manager->updateModel(model);
}

void manager::ModelManager::add(model::ModelFormat* model)
{
	this->models[model->id] = model;
	this->storage_manager->addModel(model);
}

void manager::ModelManager::clean()
{
	this->models.clear();
	this->storage_manager->clean();
}


void manager::ModelManager::processModelsInfoFile(std::string file_path)
{
	std::ifstream models_info_file(file_path, std::ifstream::in);
	GLuint models_no;
	std::string flag;
	GLint model_id = -1;
	std::string file_directory;
	std::string file_name;

	if (models_info_file.is_open())
	{
		models_info_file >> models_no;

		if (models_no == 0)
			return;

		while (!models_info_file.eof())
		{
			models_info_file >> flag;

			if (!flag.compare("-i"))
			{
				if (model_id > -1)
				{
					this->add(model_id, exec_path + file_directory, file_name);
				}

				models_info_file >> model_id;
			}
			else if (!flag.compare("-fd"))
			{
				models_info_file >> file_directory;
			}
			else if (!flag.compare("-fn"))
			{
				models_info_file >> file_name;
			}
		}

		this->add(model_id, exec_path + file_directory, file_name);
	}
}