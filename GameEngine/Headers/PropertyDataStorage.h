#pragma once


#include "PropertyDataStorage.h"
#include "ModelPropertyBuffer.h"
#include "ModelProperty.h"
#include "ModelFormat.h"


namespace storage
{
	class PropertyDataStorage
	{
	private:
		GLuint vao;

		storage::ModelPropertyBuffer model_property_storage;
		storage::ModelPropertyBuffer model_extra_property_storage;


	public:
		//------------------------------ Constructors
		PropertyDataStorage();
		PropertyDataStorage(GLuint mpb_size);

		//------------------------------ Secondary Functions (Provide Data)
		storage::ModelPropertyBuffer getModelPropertyBuffer();
		void addModelProperty(model::ModelFormat* model);
		void updateModelProperty(model::ModelFormat* model);

		storage::ModelPropertyBuffer getModelExtraPropertyBuffer();
		void addModelExtraProperty(model::ModelFormat* model);
		void updateModelExtraProperty(model::ModelFormat* model);

		void clean();
	};
}