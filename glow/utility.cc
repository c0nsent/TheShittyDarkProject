#include "utility.hpp"

namespace glow
{
	auto viewport(const i32 x, const i32 y, const isize width, const isize height) noexcept -> void
	{
		glViewport(x, y, width, height);
	}


	auto clearColor(const Color &background) noexcept -> void
	{
		glClearColor(background.red, background.green, background.blue, background.alpha);
	}
}
