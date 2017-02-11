#include "DrawIndirectCommandBufferSegment.h"




//------------------------------ Constructors

storage::DrawIndirectCommandBufferSegment::DrawIndirectCommandBufferSegment()
{

}

storage::DrawIndirectCommandBufferSegment::DrawIndirectCommandBufferSegment(GLuint start)
{
	this->start = start;
}


//------------------------------ Secondary Functions (Provide Data)

void storage::DrawIndirectCommandBufferSegment::update(GLuint start)
{
	this->start = start;
}