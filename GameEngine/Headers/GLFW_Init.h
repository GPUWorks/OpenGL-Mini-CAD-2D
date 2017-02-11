#pragma once

#include "defcs.h"




///	<summary>
///		Contains classes used for OpenGL initialization
///	</summary>
namespace core
{
	///	<summary> GLFW Initialization </summary>
	class GLFW_Init
	{
	private:
		/// <summary> Indicate the major OpenGL version </summary>
		int major_context_version;

		/// <summary> Indicate the minor OpenGL version </summary>
		int minor_context_version;

		/// <summary> Specifies which OpenGL profile to create the context for </summary>
		int opengl_profile;

		/// <summary> Specifies the desired number of samples to use for multisampling </summary>
		int msaa_factor;


	public:
		/// <summary> Default Constructor. Does nothing </summary>
		GLFW_Init();

		/// <summary> Set initialization parameters </summary>
		GLFW_Init(int major_version = 3, int minor_version = 3, int core_profile = GLFW_OPENGL_CORE_PROFILE, int msaa_factor = 4);

		/// <summary> Initialize GLFW </summary>
		void init();
	};
}