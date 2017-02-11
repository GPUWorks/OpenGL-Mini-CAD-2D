#include "IndexBufferSegment.h"




//------------------------------ Constructors

storage::IndexBufferSegment::IndexBufferSegment()
{

}

storage::IndexBufferSegment::IndexBufferSegment(GLuint start, GLuint end)
{
	this->start = start;
	this->end = end;
}


//------------------------------ Secondary Functions (Provide Data)

void storage::IndexBufferSegment::update(GLuint start, GLuint end)
{
	this->start = start;
	this->end = end;
}

void storage::IndexBufferSegment::update(GLuint end)
{
	this->end = end;
}