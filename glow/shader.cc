#include "shader.hpp"

namespace glow
{
	auto Shader::get(const Info info) const noexcept-> i32
	{
		i32 returnValue{0};
		glGetShaderiv(m_shaderId, static_cast<u32>(info), &returnValue);

		return returnValue;
	}


	Shader::Shader(const Type type, const char *source) noexcept
		: m_shaderId{glCreateShader(static_cast<u32>(type))}
	{
		glShaderSource(m_shaderId, 1, &source, nullptr);
		glCompileShader(m_shaderId);
	}


	[[nodiscard]] auto Shader::getType() const noexcept -> Type
	{
		return Type{get(Info::Type)};
	}


	auto Shader::isMarkedForDeletion() const noexcept -> bool
	{
		return get(Info::CompileStatus);
	}


	auto Shader::isCompilationSuccessful() const noexcept -> bool
	{
		return get(Info::CompileStatus);
	}


	auto Shader::getInfoLogLength() const noexcept -> u32
	{
		return get(Info::InfoLogLength);
	}


	auto Shader::getSourceLength() const noexcept -> u32
	{
		return get(Info::SourceLength);
	}


	auto Shader::getId() const noexcept -> u32
	{
		return m_shaderId;
	}


	auto Shader::getInfoLog() const -> std::string
	{
		const u32 infoLogLength{getInfoLogLength()};

		if (infoLogLength == 0) return {};

		char infoLog[infoLogLength];
		glGetShaderInfoLog(m_shaderId, infoLogLength, nullptr, infoLog);
		return infoLog;
	}


	Shader::~Shader()
	{
		glDeleteShader(m_shaderId);
	}
}