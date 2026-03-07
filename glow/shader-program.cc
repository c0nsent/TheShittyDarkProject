#include "shader-program.hpp"

#include <glad/glad.h>

namespace glow
{
	auto ShaderProgram::get(const Info info) const noexcept -> i32
	{
		i32 returnValue{};
		glGetProgramiv(m_id, static_cast<u32>(info), &returnValue);
		return returnValue;
	}


	ShaderProgram::ShaderProgram()
		: m_id{glCreateProgram()}
	{
	}


	bool ShaderProgram::createShader(const Shader::Type type, const char *path)
	{
		if (m_shaders.contains(type)) return false;

		//std::pair pair{type, Shader{type, path}};

		m_shaders.emplace(std::pair{type, Shader{}});
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


	auto ShaderProgram::isLinked() const noexcept -> bool
	{
		return get(Info::LinkStatus);
	}


	auto ShaderProgram::getLogLength() const noexcept -> isize
	{
		return get(Info::InfoLogLength);
	}


	auto ShaderProgram::hasShader(Shader::Type type) const noexcept -> bool
	{
	}


	auto ShaderProgram::getInfoLog() const -> std::string
	{
		const auto infoLogLength{getLogLength()};

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
