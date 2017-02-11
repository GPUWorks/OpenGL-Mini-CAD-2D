#pragma once


#include <iostream>
#include <vector>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include "VertexFormat.h"
#include "ModelFormat.h"
#include "MeshFormat.h"

#include "TextureLoader.h"
#include "TextureCE.h"



namespace model
{
	class ModelLoader
	{

	public:
		//------------------------------ Primary Functions
		static void loadModel(model::ModelFormat* model, std::string file_directory, std::string file_name);

	private:
		//------------------------------ Secondary Functions
		static void processMeshes(const aiScene* scene, model::ModelFormat* model, std::string file_directory);
		static void processTextures(const aiMaterial* material, mesh::MeshFormat* mesh, std::string file_directory);
		static texture::TextureFormat* loadTexture(const aiMaterial* material, aiTextureType type, std::string file_directory);
	};
}