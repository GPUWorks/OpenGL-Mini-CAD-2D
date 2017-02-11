#pragma once

#include "defcs.h"




///	<summary>
///		Contains classes used for Opengl initialization
///	</summary>
namespace core
{
	///	<summary> GLEW Initialization </summary>
	class GLEW_Init
	{
	private:
		///	<summary> Indicate whether experimental drivers are allowed or not </summary>
		GLboolean glew_experimental = GL_FALSE;

	public:
		/// <summary> Default Constructor. Does nothing </summary>
		GLEW_Init();

		/// <summary> Set initialization parameters </summary>
		GLEW_Init(GLboolean glew_experimental);

		/// <summary> Initialize GLEW </summary>
		void init();
	};
}