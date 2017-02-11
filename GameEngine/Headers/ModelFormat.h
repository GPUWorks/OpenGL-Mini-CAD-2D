#pragma once

#include <vector>

#include <GLEW\glew.h>
#include <glm\glm.hpp>

#include "MeshFormat.h"

#include "ModelCE.h"


namespace model
{
	class ModelFormat
	{
	public:
		GLuint id;
		model::CurveType ctype = model::NONE;
		GLint curves_no = 1;
		GLint curve_points_no = 15;
		GLint transformation = 0;
		
		std::vector<mesh::MeshFormat*> meshes;
	};
}