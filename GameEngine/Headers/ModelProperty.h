#pragma once

#include "ModelCE.h"



namespace model
{
	struct ModelProperty
	{
		//GLint texture_array_index;
		CurveType curve_type = CurveType::NONE;
		GLint curves_no = 1;
		GLint curve_points_no = 15;
		GLint control_points_no = 0;
		float control_points[60];
	};
}