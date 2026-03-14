#pragma once

#include "core.hpp"

#include <glad/glad.h>


//TODO: Можно использовать swap идиому чтобы не приходилось городить огромный конструкт для определения шейдера

namespace glow
{
	class Shader
	{
		enum class Info : u16;
		[[nodiscard]] auto get(Info info) const noexcept -> i32;

	public:

		enum class Type : u16;

		Shader();
		Shader(Type type, const char *path);

		[[nodiscard]] auto getType() const noexcept -> Type;
		[[nodiscard]] auto isMarkedForDeletion() const noexcept -> bool;
		[[nodiscard]] auto isCompiled() const noexcept -> bool;
		[[nodiscard]] auto getInfoLogLength() const noexcept -> isize;
		[[nodiscard]] auto getSourceLength() const noexcept -> usize;

		[[nodiscard]] auto getId() const noexcept -> u32;
		[[nodiscard]] auto getInfoLog() const -> opt<std::string>;
		auto deleteShader() const noexcept -> void;

	private:

		Type m_type;
		u32 m_id;
	};
}