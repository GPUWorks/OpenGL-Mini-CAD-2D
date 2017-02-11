#include "IndexBuffer.h"




//------------------------------ Constructors

storage::IndexBuffer::IndexBuffer()
{

}

storage::IndexBuffer::IndexBuffer(GLenum usage, GLuint indices_no, GLuint segment_indices_no)
{
	this->usage = usage;
	this->indices_no = indices_no;
	
	this->byte_index_size = sizeof(GLuint);
	this->byte_buffer_size = indices_no * byte_index_size;
	

	this->memoryAllocationAndDataInitialization();
	this->generateBuffer();
}


//------------------------------ Secondary Functions

void storage::IndexBuffer::bindBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}

void storage::IndexBuffer::generateBuffer()
{
	glGenBuffers(1, &(this->ebo));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_buffer_size, 0, usage);
}


//------------------------------ Secondary Functions (Provide Data)

GLint storage::IndexBuffer::insertData(GLuint indices_no, const void* data)
{
	ds::ibt_seg *buffer_segment = allocator.search(indices_no);

	if (buffer_segment == nullptr)
	{
		std::cout << "Index Buffer at Maximum Capacity\n";
		return -1;
	}

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, buffer_segment->offset * this->byte_index_size, indices_no * this->byte_index_size, data);

	return buffer_segment->offset;
}

void storage::IndexBuffer::insertData(GLuint offset, GLuint indices_no, const void* data)
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * this->byte_index_size, indices_no * this->byte_index_size, data);
}


//------------------------------ Secondary Functions (Retrieve Data)


void storage::IndexBuffer::memoryAllocationAndDataInitialization()
{
	this->allocator = ds::IndexBufferTree(this->indices_no, 64);
}

void storage::IndexBuffer::clean()
{
	this->allocator.clean();
}