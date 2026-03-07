#pragma once

#include "core.hpp"

#include <glad/glad.h>

#include <string>


namespace glow
{
	class Shader
	{
		enum class Info;
		[[nodiscard]] auto get(Info info) const noexcept -> i32;

	public:

		enum class Type
		{
			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER,
			Geometry = GL_GEOMETRY_SHADER,
		};

		Shader(Type type, const char *path);

		[[nodiscard]] auto getType() const noexcept -> Type;
		[[nodiscard]] auto isMarkedForDeletion() const noexcept -> bool;
		[[nodiscard]] auto isCompiled() const noexcept -> bool;
		[[nodiscard]] auto getInfoLogLength() const noexcept -> i32;
		[[nodiscard]] auto getSourceLength() const noexcept -> usize;

		[[nodiscard]] auto getId() const noexcept -> u32;
		[[nodiscard]] auto getInfoLog() const -> std::string;
		auto deleteShader() const noexcept -> void;

	private:

		u32 m_id;
	};

	enum class Shader::Info
	{
		Type = GL_SHADER_TYPE,
		DeleteStatus = GL_DELETE_STATUS,
		CompileStatus = GL_COMPILE_STATUS,
		InfoLogLength = GL_INFO_LOG_LENGTH,
		SourceLength = GL_SHADER_SOURCE_LENGTH,
	};
}