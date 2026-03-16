#pragma once

#include "core.hpp"

#include <glad/glad.h>

#include <optional>
#include <string>


namespace glow
{
	namespace detail
	{
		class BaseShader
		{
		protected:

			enum class InfoType : u16
			{
				Type = GL_SHADER_TYPE,
				DeleteStatus = GL_DELETE_STATUS,
				CompileStatus = GL_COMPILE_STATUS,
				InfoLogLength = GL_INFO_LOG_LENGTH,
				SourceLength = GL_SHADER_SOURCE_LENGTH,
			};

			enum class ShaderType : u16
			{
				Vertex = GL_VERTEX_SHADER,
				Fragment = GL_FRAGMENT_SHADER,
				Geometry = GL_GEOMETRY_SHADER,
			};

			static constexpr u32 NONE{0};

			[[nodiscard]] auto get(InfoType info) const noexcept -> i32;

			 auto compile(const char *path) const -> void;

		public:

			[[nodiscard]] auto isMarkedForDeletion() const noexcept -> bool;
			[[nodiscard]] auto isCompiled() const noexcept -> bool;
			[[nodiscard]] auto getInfoLogLength() const noexcept -> isize;
			[[nodiscard]] auto getSourceLength() const noexcept -> usize;

			[[nodiscard]] auto isExists() const noexcept -> bool;
			[[nodiscard]] auto getId() const noexcept -> u32;
			[[nodiscard]] auto getInfoLog() const -> std::optional<std::string>;
			auto deleteShader() const noexcept -> void;

			BaseShader(BaseShader &&rhs) noexcept;
			auto operator=(BaseShader &&rhs) noexcept -> BaseShader &;

			~BaseShader();

			BaseShader(const BaseShader &) = delete;
			BaseShader &operator=(const BaseShader &) = delete;

		protected:

			BaseShader() = default;
			explicit BaseShader(ShaderType type) noexcept;

			u32 m_id;
		};
	}


	class VertexShader final : public detail::BaseShader
	{
	public:

		explicit VertexShader(const char *srcPath);
	};


	class FragmentShader final : public detail::BaseShader
	{
	public:

		explicit FragmentShader(const char *srcPath);
	};


	class GeometryShader final : public detail::BaseShader
	{
	public:

		explicit GeometryShader(const char *srcPath);
	};
}