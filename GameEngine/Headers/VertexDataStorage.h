#pragma once


#include "VertexFormat.h"
#include "DrawElementsIndirectCommand.h"
#include "ModelFormat.h"
#include "MeshFormat.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "DrawIndirectCommandBuffer.h"



namespace storage
{
	class VertexDataStorage
	{
	private:
		GLuint vao;

		storage::VertexBuffer vbo;
		storage::IndexBuffer ebo;
		storage::DrawIndirectCommandBuffer dibo;

	public:
		//------------------------------ Constructors
		VertexDataStorage();
		VertexDataStorage(GLuint vbo_vertices_no, GLuint vbo_segment_vertices_no, GLuint ebo_indices_no, GLuint ebo_segment_indices_no, GLuint dibo_indirect_commands_no);

		//------------------------------ Primary Functions
		void linkVertexAttributes();
		void generateVertexArray();

		//------------------------------ Secondary Functions
		void bindVAO();

		//------------------------------ Secondary Functions (Retrieve Data)
		storage::VertexBuffer getVBO();
		storage::IndexBuffer getEBO();
		storage::DrawIndirectCommandBuffer getDIBO();

		//------------------------------ Secondary Functions (Provide Data)
		void addModel(model::ModelFormat* model);
		void updateModel(model::ModelFormat* model);

		void clean();
	};
}