#include "ModelPropertyBuffer.h"



//------------------------------ Constructors

storage::ModelPropertyBuffer::ModelPropertyBuffer()
{

}

storage::ModelPropertyBuffer::ModelPropertyBuffer(GLenum usage, GLuint buffer_size, GLuint property_size, GLuint binding_point)
{
	this->size = buffer_size;
	this->property_size = property_size;
	this->segments_no = buffer_size / property_size;
	this->usage = usage;
	this->binding_point = binding_point;

	this->all_segments = new storage::ModelPropertyBufferSegment*[this->segments_no];
	this->all_segments[0] = new storage::ModelPropertyBufferSegment[this->segments_no];
	free_segments.get_allocator().allocate(this->segments_no);


	all_segments[0]->update(0);
	free_segments.push_back(all_segments[0]);
	for (GLuint i = 1; i < this->segments_no; i++) {
		this->all_segments[i] = this->all_segments[0] + i;
		this->all_segments[i]->update(i);
		free_segments.push_back(all_segments[i]);
	}


	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, buffer_size, 0, usage);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}


//------------------------------ Secondary Functions

void storage::ModelPropertyBuffer::bindBuffer()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
}


//------------------------------ Secondary Functions (Provide Data)

GLuint storage::ModelPropertyBuffer::insertData(GLuint segment_position, const void* data)
{
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, segment_position * property_size, property_size, data);

	return segment_position;
}


GLuint storage::ModelPropertyBuffer::getBindingPoint()
{
	return this->binding_point;
}

void storage::ModelPropertyBuffer::clean()
{
	free_segments.clear();

	for (GLuint i = 0; i < this->segments_no; i++) {
		free_segments.push_back(all_segments[i]);
	}
}