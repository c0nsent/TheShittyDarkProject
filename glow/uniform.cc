#include "uniform.hpp"


namespace glow
{
	void Uniform4f::setColor(const Color &color) const noexcept
	{
		glUniform4f(m_id, color.red, color.green, color.blue, color.alpha);
	}


	Uniform4f::Uniform4f(const ShaderProgram &program, const char *name) noexcept
		: m_id{glGetUniformLocation(program.getId(), name)} {}


	Uniform4f::Uniform4f(const ShaderProgram &program, const char *name, const Color &color) noexcept
		: Uniform4f{program, name}
	{
		setColor(color);
	}
}
