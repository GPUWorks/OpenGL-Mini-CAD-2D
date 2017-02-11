#pragma once



namespace model
{
	enum CurveType
	{
		NONE = 0,
		HERMITE = 1,
		BEZIER = 2,
		BSPLINE = 4,
		NURBS = 8,
		SPLINE = 16,
		S_BEZIER = 32,
		S_SPLINE = 64,
		S_NURBS = 128,
		AXIS = 256
	};
}