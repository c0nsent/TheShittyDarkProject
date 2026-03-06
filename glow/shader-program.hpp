#pragma once

#include <glad/glad.h>

#include "core.hpp"
#include "shader.hpp"

namespace glow
{

	class ShaderProgram
	{
		enum class Info;

		[[nodiscard]] auto get(Info info) const noexcept -> i32;

		public:

		ShaderProgram(const Shader &vertex, const Shader &fragment);

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram &) = delete;
		ShaderProgram(ShaderProgram &&) = delete;
		ShaderProgram &operator=(const ShaderProgram &) = delete;

		[[nodiscard]] auto getId() const noexcept -> u32;
		[[nodiscard]] auto isLinkSuccessful() const noexcept -> bool;
		[[nodiscard]] auto getInfoLog() const -> std::string;

		auto use() const noexcept -> void;

		~ShaderProgram();

	private:

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