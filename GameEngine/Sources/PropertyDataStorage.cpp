#include "PropertyDataStorage.h"




storage::PropertyDataStorage::PropertyDataStorage()
{

}


storage::PropertyDataStorage::PropertyDataStorage(GLuint mpb_size)
{
	this->model_property_storage = storage::ModelPropertyBuffer(GL_DYNAMIC_DRAW, mpb_size, sizeof(model::ModelProperty), 0);
	this->model_extra_property_storage = storage::ModelPropertyBuffer(GL_DYNAMIC_DRAW, mpb_size, sizeof(model::ExtraModelProperty), 1);
}

storage::ModelPropertyBuffer storage::PropertyDataStorage::getModelPropertyBuffer()
{
	return this->model_property_storage;
}

storage::ModelPropertyBuffer storage::PropertyDataStorage::getModelExtraPropertyBuffer()
{
	return this->model_extra_property_storage;
}


void storage::PropertyDataStorage::addModelProperty(model::ModelFormat* model)
{
	this->model_property_storage.bindBuffer();

	for (mesh::MeshFormat* mesh : model->meshes) {
		mesh->model_property.curve_type = model->ctype;
		mesh->model_property.curves_no = model->curves_no;
		mesh->model_property.curve_points_no = model->curve_points_no;
		mesh->model_property.control_points_no = mesh->vertices.size();

		int j = 0;
		for (GLuint i = 0; i < mesh->vertices.size(); i++)
		{
			mesh->model_property.control_points[j++] = mesh->vertices[i].position.x;
			mesh->model_property.control_points[j++] = mesh->vertices[i].position.y;
			mesh->model_property.control_points[j++] = mesh->vertices[i].position.z;
		}

		this->model_property_storage.insertData(mesh->draw_command.base_instance, &(mesh->model_property));
	}
}

void storage::PropertyDataStorage::updateModelProperty(model::ModelFormat* model)
{
	this->model_property_storage.bindBuffer();

	for (mesh::MeshFormat* mesh : model->meshes) {
		mesh->model_property.curve_type = model->ctype;
		mesh->model_property.curves_no = model->curves_no;
		mesh->model_property.curve_points_no = model->curve_points_no;
		mesh->model_property.control_points_no = mesh->vertices.size();

		int j = 0;
		for (GLuint i = 0; i < mesh->vertices.size(); i++)
		{
			mesh->model_property.control_points[j++] = mesh->vertices[i].position.x;
			mesh->model_property.control_points[j++] = mesh->vertices[i].position.y;
			mesh->model_property.control_points[j++] = mesh->vertices[i].position.z;
		}

		this->model_property_storage.insertData(mesh->draw_command.base_instance, &(mesh->model_property));
	}
}

void storage::PropertyDataStorage::addModelExtraProperty(model::ModelFormat* model)
{
	this->model_extra_property_storage.bindBuffer();

	for (mesh::MeshFormat* mesh : model->meshes) {
		mesh->extra_model_property.transformation = model->transformation;

		this->model_extra_property_storage.insertData(mesh->draw_command.base_instance, &(mesh->extra_model_property));
	}
}

void storage::PropertyDataStorage::updateModelExtraProperty(model::ModelFormat* model)
{
	this->model_extra_property_storage.bindBuffer();

	for (mesh::MeshFormat* mesh : model->meshes) {
		mesh->extra_model_property.transformation = model->transformation;

		this->model_extra_property_storage.insertData(mesh->draw_command.base_instance, &(mesh->extra_model_property));
	}
}

void storage::PropertyDataStorage::clean()
{
	this->model_property_storage.clean();
	this->model_extra_property_storage.clean();
}