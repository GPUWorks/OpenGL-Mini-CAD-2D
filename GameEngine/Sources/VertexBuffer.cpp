#include "VertexBuffer.h"




//------------------------------ Constructors

storage::VertexBuffer::VertexBuffer()
{

}

storage::VertexBuffer::VertexBuffer(GLenum usage, GLuint vertices_no, GLuint segment_vertices_no)
{
	this->usage = usage;
	this->vertices_no = vertices_no;

	this->byte_vertex_size = sizeof(vertex::VertexFormat);
	this->byte_buffer_size = vertices_no * byte_vertex_size;

	this->memoryAllocationAndDataInitialization();
	this->generateBuffer();
}


//------------------------------ Secondary Functions

void storage::VertexBuffer::bindBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}

void storage::VertexBuffer::generateBuffer()
{
	glGenBuffers(1, &(this->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, byte_buffer_size, 0, usage);
}


//------------------------------ Secondary Functions (Provide Data)

GLint storage::VertexBuffer::insertData(GLuint vertices_no, const void* data)
{
	ds::vbt_seg *buffer_segment = allocator.search(vertices_no);

	if (buffer_segment == nullptr)
	{
		std::cout << "Vertex Buffer at Maximum Capacity\n";
		return -1;
	}

	glBufferSubData(GL_ARRAY_BUFFER, buffer_segment->offset * this->byte_vertex_size, vertices_no * this->byte_vertex_size, data);

	return buffer_segment->offset;
}

void storage::VertexBuffer::insertData(GLuint offset, GLuint vertices_no, const void* data)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset * this->byte_vertex_size, vertices_no * this->byte_vertex_size, data);
}


//------------------------------ Secondary Functions (Retrieve Data)

void storage::VertexBuffer::memoryAllocationAndDataInitialization()
{
	this->allocator = ds::VertexBufferTree(this->vertices_no, 64);
}

void storage::VertexBuffer::clean()
{
	this->allocator.clean();
}