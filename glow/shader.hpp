#pragma once

#include <string>

#include "core.hpp"

namespace glow
{
	class Shader
	{
		enum class Info;
		auto get(Info info) const noexcept -> i32;

	public:
		enum class Type;

		explicit Shader(Type type, const char * source) noexcept;
		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;

		[[nodiscard]] auto getType() const noexcept -> Type;
		[[nodiscard]] auto isMarkedForDeletion() const noexcept -> bool;
		[[nodiscard]] auto isCompilationSuccessful() const noexcept -> bool;
		[[nodiscard]] auto getInfoLogLength() const noexcept -> u32;
		[[nodiscard]] auto getSourceLength() const noexcept -> u32;

		[[nodiscard]] auto getId() const noexcept -> u32;
		[[nodiscard]] auto getInfoLog() const -> std::string;

		~Shader();

	private:

		u32 m_shaderId;
	};

	enum class Shader::Info
	{
		Type = GL_SHADER_TYPE,
		DeleteStatus = GL_DELETE_STATUS,
		CompileStatus = GL_COMPILE_STATUS,
		InfoLogLength = GL_INFO_LOG_LENGTH,
		SourceLength = GL_SHADER_SOURCE_LENGTH,
	};

	enum class Shader::Type
	{
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
	};

}