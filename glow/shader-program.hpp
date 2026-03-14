#pragma once

#include <glad/glad.h>

#include "core.hpp"
#include "shader.hpp"

#include <initializer_list>
#include <boost/container/small_vector.hpp>
#include <boost/unordered/unordered_flat_map.hpp>

namespace glow
{
	class ShaderProgram
	{
		enum class Info;

		[[nodiscard]] auto get(Info info) const noexcept -> i32;
		[[nodiscard]] static auto getShaderTypeIndex(Shader::Type type) noexcept -> size_t;

	public:

		ShaderProgram(std::initializer_list<Shader> &&shaders);

		ShaderProgram(const ShaderProgram &) = delete;
		ShaderProgram(ShaderProgram &&) = delete;
		ShaderProgram &operator=(const ShaderProgram &) = delete;

		[[nodiscard]] auto getId() const noexcept -> u32;
		[[nodiscard]] auto isLinked() const noexcept -> bool;
		[[nodiscard]] auto getLogLength() const noexcept -> isize;
		[[nodiscard]] auto getInfoLog() const -> std::string;
		[[nodiscard]] auto hasShader() const noexcept -> bool;
		[[nodiscard]] auto hasShader(Shader::Type type) const noexcept-> bool;
		[[nodiscard]] auto getShader(Shader::Type type) const noexcept -> const Shader &;

		auto use() const noexcept -> void;

	private:

		boost::unordered::unordered_flat_map<Shader::Type, Shader> m_shaders;
		u32 m_id;
	};

	enum class ShaderProgram::Info
	{
		DeleteStatus = GL_DELETE_STATUS,
		LinkStatus = GL_LINK_STATUS,
		ValidateStatus = GL_VALIDATE_STATUS,
		InfoLogLength = GL_INFO_LOG_LENGTH,
		AttachedShaders = GL_ATTACHED_SHADERS,
	};
}