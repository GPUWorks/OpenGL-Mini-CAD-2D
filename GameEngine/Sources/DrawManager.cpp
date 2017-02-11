#include "DrawManager.h"



//------------------------------ Singleton Pattern

manager::DrawManager* manager::DrawManager::getInstance()
{
	static DrawManager instance;

	return &instance;
}


//------------------------------ Primary Functions

void manager::DrawManager::init(manager::StorageManager* stm, manager::ShaderManager* shm, manager::CameraManager* cm)
{
	this->storage_manager = stm;
	this->shader_manager = shm;
	this->camera_manager = cm;
}

void manager::DrawManager::listener()
{
	this->drawModels();
}

void manager::DrawManager::drawModels()
{
	glPointSize(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shader_manager->getShader(0)->getProgram());
	
	this->camera_manager->setPlayerCameraUniforms(shader_manager->getShader(0)->getProgram());

	this->storage_manager->getTextureDataStorage()->getArray2DSquareTextureBuffer().bindTexture();
	this->storage_manager->getModelDataStorage()->bindVAO();
	glMultiDrawElementsIndirect(GL_POINTS, GL_UNSIGNED_INT, 0, this->storage_manager->getModelDataStorage()->getDIBO().getActiveIndirectCommandsNo(), 0);


	glPointSize(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shader_manager->getShader(2)->getProgram());

	this->camera_manager->setPlayerCameraUniforms(shader_manager->getShader(2)->getProgram());

	this->storage_manager->getTextureDataStorage()->getArray2DSquareTextureBuffer().bindTexture();
	this->storage_manager->getModelDataStorage()->bindVAO();
	glMultiDrawElementsIndirect(GL_POINTS, GL_UNSIGNED_INT, 0, this->storage_manager->getModelDataStorage()->getDIBO().getActiveIndirectCommandsNo(), 0);



	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	glUseProgram(shader_manager->getShader(1)->getProgram());

	this->camera_manager->setPlayerCameraUniforms(shader_manager->getShader(1)->getProgram());

	this->storage_manager->getTextureDataStorage()->getArray2DSquareTextureBuffer().bindTexture();
	this->storage_manager->getModelDataStorage()->bindVAO();
	glMultiDrawElementsIndirect(GL_POINTS, GL_UNSIGNED_INT, 0, this->storage_manager->getModelDataStorage()->getDIBO().getActiveIndirectCommandsNo(), 0);
}