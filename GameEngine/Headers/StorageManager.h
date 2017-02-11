#pragma once

#include <map>
#include <vector>

#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include "VertexDataStorage.h"
#include "TextureDataStorage.h"
#include "DrawElementsIndirectCommand.h"
#include "PropertyDataStorage.h"


namespace manager
{
	class StorageManager
	{
	private:
		storage::VertexDataStorage* vertex_data_storage;
		storage::TextureDataStorage* texture_data_storage;
		storage::PropertyDataStorage* property_data_storage;


		//------------------------------ Constructors
		StorageManager() {};
		~StorageManager() {};

	public:
		//------------------------------ Singleton Pattern
		StorageManager(const StorageManager &) = delete;
		const StorageManager &operator=(const StorageManager &) = delete;
		static StorageManager* getInstance();

		//------------------------------ Primary Functions
		void init();
		void listener();
		void clean();

		//------------------------------ Secondary Functions (Provide Data)
		void addModel(model::ModelFormat* model);
		void updateModel(model::ModelFormat* model);

		//------------------------------ Secondary Functions (Retrieve Data)
		storage::VertexDataStorage* getModelDataStorage();
		storage::TextureDataStorage* getTextureDataStorage();
		storage::PropertyDataStorage* getPropertyDataStorage();
	};
}