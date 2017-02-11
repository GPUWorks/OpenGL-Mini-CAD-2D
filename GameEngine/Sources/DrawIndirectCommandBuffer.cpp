#include "DrawIndirectCommandBuffer.h"




//------------------------------ Constructors

storage::DrawIndirectCommandBuffer::DrawIndirectCommandBuffer()
{

}

storage::DrawIndirectCommandBuffer::DrawIndirectCommandBuffer(GLenum usage, GLuint indirect_commands_no)
{
	this->usage = usage;
	this->indirect_commands_no = indirect_commands_no;

	this->byte_indirect_command_size = sizeof(storage::DrawElementsIndirectCommand);
	this->byte_buffer_size = indirect_commands_no * byte_indirect_command_size;

	this->clear_data = new storage::DrawElementsIndirectCommand[indirect_commands_no];

	this->memoryAllocationAndDataInitialization();
	this->generateBuffer();
}


//------------------------------ Secondary Functions

void storage::DrawIndirectCommandBuffer::bindBuffer()
{
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, this->dibo);
}

void storage::DrawIndirectCommandBuffer::generateBuffer()
{
	glGenBuffers(1, &(this->dibo));
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, this->dibo);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, this->byte_buffer_size, 0, usage);
}


//------------------------------ Secondary Functions (Provide Data)

GLint storage::DrawIndirectCommandBuffer::insertData(const void* data)
{
	ds::dicbt_seg *buffer_segment = allocator.search(1);

	if (buffer_segment == nullptr)
	{
		std::cout << "Indirect Commands at Maximum Capacity\n";
		return -1;
	}

	storage::DrawElementsIndirectCommand* indirect_command = (storage::DrawElementsIndirectCommand*) data;
	indirect_command->base_instance = buffer_segment->offset;

	glBufferSubData(GL_DRAW_INDIRECT_BUFFER, buffer_segment->offset * this->byte_indirect_command_size, this->byte_indirect_command_size, data);

	return buffer_segment->offset;
}

void storage::DrawIndirectCommandBuffer::insertData(GLuint offset, const void* data)
{

	glBufferSubData(GL_DRAW_INDIRECT_BUFFER, offset * this->byte_indirect_command_size, this->byte_indirect_command_size, data);
}


//------------------------------ Secondary Functions (Retrieve Data)

GLuint storage::DrawIndirectCommandBuffer::getActiveIndirectCommandsNo()
{
	return this->indirect_commands_no;
}

void storage::DrawIndirectCommandBuffer::memoryAllocationAndDataInitialization()
{
	this->allocator = ds::DrawIndirectCommandBufferTree(this->indirect_commands_no, 1);
}

void storage::DrawIndirectCommandBuffer::clean()
{
	this->allocator.clean();

	this->bindBuffer();
	glBufferSubData(GL_DRAW_INDIRECT_BUFFER, 0, indirect_commands_no * this->byte_indirect_command_size, (void*)clear_data);
}