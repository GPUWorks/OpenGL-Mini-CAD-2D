#include "ModelLoader.h"



//------------------------------ Primary Functions

void model::ModelLoader::loadModel(model::ModelFormat* model, std::string file_directory, std::string file_name)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(file_directory + "/" + file_name, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		std::cout << "Assimp Error" << importer.GetErrorString() << std::endl;

	processMeshes(scene, model, file_directory);
}


//------------------------------ Secondary Functions

void model::ModelLoader::processMeshes(const aiScene* scene, model::ModelFormat* model, std::string file_directory)
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;

	for (GLuint k = 0; k < scene->mNumMeshes; k++) {
		const aiMesh* mesh = scene->mMeshes[k];

		mesh::MeshFormat* mf = new mesh::MeshFormat();

		for (GLuint i = 0; i < mesh->mNumVertices; i++) {
			position.x = mesh->mVertices[i].x;
			position.y = mesh->mVertices[i].y;
			position.z = mesh->mVertices[i].z;

			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;

			if (mesh->mTextureCoords[0]) {
				texture.x = mesh->mTextureCoords[0][i].x;
				texture.y = mesh->mTextureCoords[0][i].y;
			}
			else
				texture = glm::vec2(0.0f, 0.0f);

			/*if (mesh->mMaterialIndex == 3) {
				texture.x /= 8;
				texture.y /= 8;
			}*/

			mf->vertices.push_back(vertex::VertexFormat(position, normal, texture));
		}

		for (GLuint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (GLuint j = 0; j < face.mNumIndices; j++)
				mf->indices.push_back(face.mIndices[j]);
		}

		mf->draw_command.count = mf->indices.size();
		mf->draw_command.instance_count = 1;
		mf->draw_command.first_index = 0;
		mf->draw_command.base_vertex = -1;
		mf->draw_command.base_instance = -1;

		if (mesh->mMaterialIndex >= 0) {
			processTextures(scene->mMaterials[mesh->mMaterialIndex], mf, file_directory);
		}

		model->meshes.push_back(mf);
	}
}

void model::ModelLoader::processTextures(const aiMaterial* material, mesh::MeshFormat* mesh, std::string file_directory)
{
	if (material->GetTextureCount(aiTextureType_DIFFUSE))
		mesh->textures[texture::TEXTURE_DIFFUSE] = loadTexture(material, aiTextureType_DIFFUSE, file_directory);

	//if (material->GetTextureCount(aiTextureType_SPECULAR))
	//	mesh->textures[texture::TEXTURE_SPECULAR] = loadTexture(material, aiTextureType_SPECULAR, file_directory);
}

texture::TextureFormat* model::ModelLoader::loadTexture(const aiMaterial* material, aiTextureType type, std::string file_directory)
{
	aiString str;
	material->GetTexture(type, 0, &str);

	texture::TextureFormat* tf = texture::TextureLoader::loadImage(file_directory + "/" + str.C_Str());

	std::cout << str.C_Str() << std::endl;

	return tf;
}