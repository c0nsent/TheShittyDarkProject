#include "shader-program.hpp"

#include <array>
#include <stdexcept>
#include <unordered_set>
#include <glad/glad.h>

namespace glow
{
	auto ShaderProgram::get(const Info info) const noexcept -> i32
	{
		i32 returnValue{};
		glGetProgramiv(m_id, static_cast<u32>(info), &returnValue);
		return returnValue;
	}


	ShaderProgram::ShaderProgram(std::initializer_list<Shader> &&shaders)
		: m_id{glCreateProgram()}
	{
		std::unordered_set<Shader::Type> shaderTypes;

		for (const Shader shader : shaders)
		{
			if (shaderTypes.contains(shader.getType()))
				throw std::runtime_error{"Error passed same type"}; //TODO: Временно

			shaderTypes.insert(shader.getType());

			glAttachShader(m_id, shader.getId());
			glDeleteShader(shader.getId());
		}
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


	auto ShaderProgram::getInfoLog() const -> std::string
	{
		const auto infoLogLength{getLogLength()};

		if (infoLogLength == 0) return {};

		char infoLog[infoLogLength];
		glGetProgramInfoLog(m_id, infoLogLength, nullptr, infoLog);

		return infoLog;
	}


	auto ShaderProgram::hasShader() const noexcept -> bool
	{
		return get(Info::AttachedShaders) != 0;
	}


	auto ShaderProgram::hasShader(const Shader::Type type) const noexcept -> bool
	{
		std::array<u32, SHADER_TYPE_COUNT> shaders{};
		glGetAttachedShaders(m_id, shaders.size(), nullptr, shaders.data());

		for (const u32 shader : shaders)
		{
			b32 isRequiredType;
			glGetShaderiv(shader, static_cast<u32>(type), &isRequiredType);

			return isRequiredType;
		}

		return false;
	}


	auto ShaderProgram::use() const noexcept -> void
	{
		glUseProgram(m_id);
	}
}
