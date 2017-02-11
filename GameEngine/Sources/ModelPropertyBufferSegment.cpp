#include "ModelPropertyBufferSegment.h"




//------------------------------ Constructors

storage::ModelPropertyBufferSegment::ModelPropertyBufferSegment()
{

}

storage::ModelPropertyBufferSegment::ModelPropertyBufferSegment(GLuint position)
{
	this->position = position;
}


void storage::ModelPropertyBufferSegment::update(GLuint position)
{
	this->position = position;
}