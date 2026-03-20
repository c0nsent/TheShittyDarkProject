#pragma once

#include <glad/glad.h>

#include "basic-types.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


namespace glow
{
	class Texture final
	{

	public:

		Texture(const char *path);

	private:

		u32 m_id;
	};
}