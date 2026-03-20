#pragma once

#include "basic-types.hpp"
#include "shader-program.hpp"


namespace glow
{
	class Uniform4f final
	{
	public:

		void setColor(const Color &color) const noexcept;
		Uniform4f(const ShaderProgram &program, const char *name) noexcept;
		Uniform4f(const ShaderProgram &program, const char *name, const Color &color) noexcept;

	private:

		i32 m_id;
	};
}