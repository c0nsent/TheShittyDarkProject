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


	Shader::Shader()
	{

	}


	Shader::Shader(const Type type, const char *path)
		: m_type{type}, m_id{glCreateShader(std::to_underlying(type))}
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
		return m_type;
	}


	auto Shader::isMarkedForDeletion() const noexcept -> bool
	{
		return get(Info::DeleteStatus);
	}


	auto Shader::isCompiled() const noexcept -> bool
	{
		return get(Info::CompileStatus);
	}


	auto Shader::getInfoLogLength() const noexcept -> isize
	{
		return get(Info::InfoLogLength);
	}


	auto Shader::getSourceLength() const noexcept -> usize
	{
		return get(Info::SourceLength);
	}


	auto Shader::getId() const noexcept -> u32
	{
		return m_id;
	}


	auto Shader::getInfoLog() const -> opt<std::string>
	{
		const isize infoLogLength{getInfoLogLength()};

		if (infoLogLength == 0) return boost::none;

		std::string infoLog;
		glGetShaderInfoLog(m_id, infoLogLength, nullptr, infoLog.data());

		return boost::make_optional(std::move(infoLog));
	}


	auto Shader::deleteShader() const noexcept -> void
	{
		glDeleteShader(m_id);
	}
}
