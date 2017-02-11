#include "VertexBufferSegment.h"




//------------------------------ Constructors

storage::VertexBufferSegment::VertexBufferSegment()
{

}

storage::VertexBufferSegment::VertexBufferSegment(GLuint start, GLuint end)
{
	this->start = start;
	this->end = end;
}


//------------------------------ Secondary Functions (Provide Data)

void storage::VertexBufferSegment::update(GLuint start, GLuint end)
{
	this->start = start;
	this->end = end;
}

void storage::VertexBufferSegment::update(GLuint end)
{
	this->end = end;
}