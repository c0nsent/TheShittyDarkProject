#pragma once

#include <glad/glad.h>

#include "basic-types.hpp"


namespace glow
{
	auto viewport(i32 x, i32 y, isize width, isize height) noexcept -> void;
	auto clearColor(const Color &background) noexcept -> void;
}
