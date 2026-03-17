#pragma once

#include <glad/glad.h>

#include "core.hpp"
#include "shader.hpp"

#include <tuple>


namespace glow
{
	class ShaderProgram final
	{
		enum class InfoType : u16
		{
			DeleteStatus = GL_DELETE_STATUS,
			LinkStatus = GL_LINK_STATUS,
			ValidateStatus = GL_VALIDATE_STATUS,
			InfoLogLength = GL_INFO_LOG_LENGTH,
			AttachedShaders = GL_ATTACHED_SHADERS,
		};

		[[nodiscard]] auto get(InfoType info) const noexcept -> i32;

	public:

		struct CreateInfo final
		{
			VertexShader vertexShader;
			FragmentShader fragmentShader;
			GeometryShader geometryShader;
		};

		ShaderProgram(CreateInfo &&createInfo);

		~ShaderProgram();

		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram &) = delete;
		ShaderProgram(ShaderProgram &&) = delete;
		ShaderProgram &operator=(const ShaderProgram &) = delete;

		[[nodiscard]] auto getId() const noexcept -> u32;
		[[nodiscard]] auto isLinked() const noexcept -> bool;
		[[nodiscard]] auto getLogLength() const noexcept -> isize;
		[[nodiscard]] auto getInfoLog() const -> std::optional<std::string>;

		template<class T> requires std::derived_from<T, detail::BaseShader>
		[[nodiscard]] auto hasShader() const noexcept -> bool;

		template<class T> requires std::derived_from<T, detail::BaseShader>
		[[nodiscard]] auto getShader() const noexcept -> T &;

		auto use() const noexcept -> void;

	private:

		std::tuple<VertexShader, FragmentShader, GeometryShader> m_shaders;

		u32 m_id;
	};
}
