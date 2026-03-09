#pragma once

#include "core.hpp"

#include <source_location>


namespace glow
{
	class Error
	{

	public:

		enum class Code : u16
		{
			NoError = GL_NO_ERROR,
			InvalidEnum = GL_INVALID_ENUM,
			InvalidValue = GL_INVALID_VALUE,
			InvalidOperation = GL_INVALID_OPERATION,
			StackOverflow = GL_STACK_OVERFLOW,
			StackUnderflow = GL_STACK_UNDERFLOW,
			OutOfMemory = GL_OUT_OF_MEMORY,
			InvalidFrameBufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
		};

		[[nodiscard]] static auto last() noexcept -> Code;
		static auto print(Code code = last(), const std::source_location &loc = std::source_location::current()) -> void;

	private:

		[[nodiscard]] static auto toString(Code code) -> const char *;
	};
}
