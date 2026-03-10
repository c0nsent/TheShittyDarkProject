#pragma once

#include "core.hpp"

#include <source_location>


namespace glow
{
	class Error
	{
		using src_loc = std::source_location;
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
		static auto print(Code code = last(), const src_loc &loc = src_loc::current()) -> void;
		static auto printIfError(Code code = last(), const src_loc &loc = src_loc::current()) -> void;

	private:

		[[nodiscard]] static auto toString(Code code) -> const char *;
	};
}
