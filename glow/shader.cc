#include "shader.hpp"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <string>

namespace glow
{
	auto Shader::get(const Info info) const noexcept-> i32
	{
		i32 returnValue{0};
		glGetShaderiv(m_id, static_cast<u32>(info), &returnValue);

		return returnValue;
	}


	Shader::Shader(const Type type, const char *path)
		: m_id{glCreateShader(static_cast<u32>(type))}
	{
		std::ifstream file{path};
		std::ostringstream oss;
		oss << file.rdbuf();
		const std::string srcString{oss.str()};
		const char *src{srcString.c_str()};

		glShaderSource(m_id, 1, &src, nullptr);
		glCompileShader(m_id);
	}


	[[nodiscard]] auto Shader::getType() const noexcept -> Type
	{
		return Type{get(Info::Type)};
	}


	auto Shader::isMarkedForDeletion() const noexcept -> bool
	{
		return get(Info::CompileStatus);
	}


	auto Shader::isCompiled() const noexcept -> bool
	{
		return get(Info::CompileStatus);
	}


	auto Shader::getInfoLogLength() const noexcept -> isize
	{
		return get(Info::InfoLogLength);
	}


	auto Shader::getSourceLength() const noexcept -> u32
	{
		return get(Info::SourceLength);
	}


	auto Shader::getId() const noexcept -> u32
	{
		return m_id;
	}


	auto Shader::getInfoLog() const -> std::string
	{
		const isize infoLogLength{getInfoLogLength()};

		if (infoLogLength == 0) return {};

		char infoLog[infoLogLength];
		glGetShaderInfoLog(m_id, infoLogLength, nullptr, infoLog);
		return infoLog;
	}


	auto Shader::deleteShader() const noexcept -> void
	{
		glDeleteShader(m_id);
	}
}
