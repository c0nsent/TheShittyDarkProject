#include "shader-program.hpp"


namespace glow
{
	auto ShaderProgram::get(const Info info) const noexcept -> i32
	{
		i32 returnValue{};
		glGetProgramiv(m_id, static_cast<u32>(info), &returnValue);
		return returnValue;
	}


	ShaderProgram::ShaderProgram(const Shader &vertex, const Shader &fragment)
		: m_id{glCreateProgram()}
	{
		glAttachShader(m_id, vertex.getId());
		glAttachShader(m_id, fragment.getId());
		glLinkProgram(m_id);
	}


	auto ShaderProgram::getId() const noexcept -> u32
	{
		return m_id;
	}


	auto ShaderProgram::isLinkSuccessful() const noexcept -> bool
	{
		return get(Info::LinkStatus);
	}


	auto ShaderProgram::getInfoLog() const -> std::string
	{
		const u32 infoLogLength{static_cast<u32>(get(Info::InfoLogLength))};

		if (infoLogLength == 0) return {};

		char infoLog[infoLogLength];
		glGetProgramInfoLog(m_id, infoLogLength, nullptr, infoLog);

		return infoLog;
	}


	auto ShaderProgram::use() const noexcept -> void
	{
		glUseProgram(m_id);
	}


	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_id);
	}
}
