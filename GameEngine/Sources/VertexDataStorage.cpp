#include "VertexDataStorage.h"



//------------------------------ Constructors

storage::VertexDataStorage::VertexDataStorage()
{

}

storage::VertexDataStorage::VertexDataStorage(GLuint vbo_vertices_no, GLuint vbo_segment_vertices_no, GLuint ebo_indices_no, GLuint ebo_segment_indices_no, GLuint dibo_indirect_commands_no)
{
	this->vbo = storage::VertexBuffer(GL_DYNAMIC_DRAW, vbo_vertices_no, vbo_segment_vertices_no);
	this->ebo = storage::IndexBuffer(GL_DYNAMIC_DRAW, ebo_indices_no, ebo_segment_indices_no);
	this->dibo = storage::DrawIndirectCommandBuffer(GL_DYNAMIC_DRAW, dibo_indirect_commands_no);

	this->generateVertexArray();
}


//------------------------------ Primary Functions

void storage::VertexDataStorage::linkVertexAttributes()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex::VertexFormat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex::VertexFormat), (void*)(offsetof(vertex::VertexFormat, vertex::VertexFormat::normal)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex::VertexFormat), (void*)(offsetof(vertex::VertexFormat, vertex::VertexFormat::texture)));

}

void storage::VertexDataStorage::generateVertexArray()
{
	glGenVertexArrays(1, &(this->vao));
	glBindVertexArray(this->vao);

	this->vbo.bindBuffer();
	this->ebo.bindBuffer();
	this->dibo.bindBuffer();

	this->linkVertexAttributes();

	glBindVertexArray(0);
}


//------------------------------ Secondary Functions

void storage::VertexDataStorage::bindVAO()
{
	glBindVertexArray(this->vao);
}


//------------------------------ Secondary Functions (Retrieve Data)

storage::VertexBuffer storage::VertexDataStorage::getVBO()
{
	return this->vbo;
}

storage::IndexBuffer storage::VertexDataStorage::getEBO()
{
	return this->ebo;
}

storage::DrawIndirectCommandBuffer storage::VertexDataStorage::getDIBO()
{
	return this->dibo;
}


//------------------------------ Secondary Functions (Provide Data)

void storage::VertexDataStorage::addModel(model::ModelFormat* model)
{
	this->vbo.bindBuffer();
	this->ebo.bindBuffer();
	this->dibo.bindBuffer();

	for (mesh::MeshFormat* mesh : model->meshes) {
		mesh->inserted = true;

		if (model->ctype == model::S_BEZIER || model->ctype == model::S_SPLINE || model->ctype == model::S_NURBS)
			mesh->draw_command.instance_count = model->curve_points_no;
		else
			mesh->draw_command.instance_count = model->curves_no;

		mesh->draw_command.base_vertex = vbo.insertData(mesh->vertices.size(), &(mesh->vertices[0]));
		mesh->draw_command.first_index = ebo.insertData(mesh->indices.size(), &(mesh->indices[0]));
		mesh->draw_command.base_instance = dibo.insertData(&(mesh->draw_command));
	}
}

void storage::VertexDataStorage::updateModel(model::ModelFormat* model)
{
	this->vbo.bindBuffer();
	this->ebo.bindBuffer();
	this->dibo.bindBuffer();

	for (mesh::MeshFormat* mesh : model->meshes) {
		if (mesh->inserted == false)
		{
			mesh->inserted = true;

			if (model->ctype == model::S_BEZIER || model->ctype == model::S_SPLINE || model->ctype == model::S_NURBS)
				mesh->draw_command.instance_count = model->curve_points_no;
			else
				mesh->draw_command.instance_count = model->curves_no;

			mesh->draw_command.base_vertex = vbo.insertData(mesh->vertices.size(), &(mesh->vertices[0]));
			mesh->draw_command.first_index = ebo.insertData(mesh->indices.size(), &(mesh->indices[0]));
			mesh->draw_command.base_instance = dibo.insertData(&(mesh->draw_command));
		}
		else {
			if (model->ctype == model::S_BEZIER || model->ctype == model::S_SPLINE || model->ctype == model::S_NURBS)
				mesh->draw_command.instance_count = model->curve_points_no;
			else
				mesh->draw_command.instance_count = model->curves_no;

			vbo.insertData(mesh->draw_command.base_vertex, mesh->vertices.size(), &(mesh->vertices[0]));
			ebo.insertData(mesh->draw_command.first_index, mesh->indices.size(), &(mesh->indices[0]));
			dibo.insertData(mesh->draw_command.base_instance, &(mesh->draw_command));
		}
	}
}

void storage::VertexDataStorage::clean()
{
	this->vbo.clean();
	this->ebo.clean();
	this->dibo.clean();
}