#pragma once

#include "core.hpp"

#include <glad/glad.h>


namespace
{
	class Loader
	{
	public:

		Loader(void* (* GLADloadproc)(const char *name));

	};
}