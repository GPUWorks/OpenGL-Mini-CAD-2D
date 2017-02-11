#include "StorageManager.h"



//------------------------------ Singleton Pattern

manager::StorageManager* manager::StorageManager::getInstance()
{
	static StorageManager instance;

	return &instance;
}


//------------------------------ Primary Functions

void manager::StorageManager::init()
{
	this->vertex_data_storage = new storage::VertexDataStorage(5048576, 0, 5048576, 0, 2048);
	this->texture_data_storage = new storage::TextureDataStorage(1, GL_RGB8, GL_RGB, 1024, 1024, 64, 50);
	this->property_data_storage = new storage::PropertyDataStorage(10000 * sizeof(model::ModelProperty));
}

void manager::StorageManager::listener()
{
	
}

void manager::StorageManager::clean()
{
	this->vertex_data_storage->clean();
	this->property_data_storage->clean();
}


//------------------------------ Secondary Functions (Provide Data)

void manager::StorageManager::addModel(model::ModelFormat* model)
{
	this->vertex_data_storage->addModel(model);
	//this->texture_data_storage->addModelTexture(model);
	this->property_data_storage->addModelProperty(model);
	this->property_data_storage->addModelExtraProperty(model);
}

void manager::StorageManager::updateModel(model::ModelFormat* model)
{
	this->vertex_data_storage->updateModel(model);
	//this->texture_data_storage->addModelTexture(model);
	this->property_data_storage->updateModelProperty(model);
	this->property_data_storage->updateModelExtraProperty(model);
}


//------------------------------ Secondary Functions (Retrieve Data)

storage::VertexDataStorage* manager::StorageManager::getModelDataStorage()
{
	return this->vertex_data_storage;
}

storage::TextureDataStorage* manager::StorageManager::getTextureDataStorage()
{
	return this->texture_data_storage;
}

storage::PropertyDataStorage* manager::StorageManager::getPropertyDataStorage()
{
	return this->property_data_storage;
}