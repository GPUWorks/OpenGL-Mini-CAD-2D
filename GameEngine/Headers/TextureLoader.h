#pragma once

#include <SOIL\SOIL.h>

#include "TextureFormat.h"


namespace texture
{
	class TextureLoader
	{
	private:
		//------------------------------ Constructors
		TextureLoader() {};

	public:
		//------------------------------ Primary Functions
		static texture::TextureFormat* loadImage(std::string filename);
	};
}