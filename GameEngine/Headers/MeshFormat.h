#pragma once

#include <vector>
#include <map>

#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include "DrawElementsIndirectCommand.h"
#include "VertexFormat.h"
#include "TextureFormat.h"
#include "TextureCE.h"

#include "ModelProperty.h"
#include "ExtraModelProperty.h"


namespace mesh
{
	class MeshFormat
	{
	public:
		std::vector<vertex::VertexFormat> vertices;
		std::vector<GLuint> indices;
		storage::DrawElementsIndirectCommand draw_command;

		model::ModelProperty model_property;

		model::ExtraModelProperty extra_model_property;

		std::map<texture::TextureCE, texture::TextureFormat*> textures;

		bool inserted = false;
	};
}