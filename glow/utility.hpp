#pragma once

#include "core.hpp"

#include <source_location>
#include <tuple>
#include <string>
#include <unordered_map>
#include <utility>


namespace glow
{
	///Todo: Можно реализовать вызов по типу коллбэков.
	class Error final
	{
		using sl = std::source_location;
	public:

		enum class Code
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

		static auto checkAndPrint(sl &&loc = sl::current()) -> void;


		[[nodiscard]] static auto hasError(sl &&loc = sl::current()) noexcept -> bool;
		[[nodiscard]] static auto check(sl &&loc = sl::current()) noexcept -> Code;
		static auto print(sl &&loc = sl::current()) noexcept -> void;

		[[nodiscard]] auto code() const noexcept -> Code;
		[[nodiscard]] auto location() const noexcept -> sl;

		auto operator=(const Error &rhs) noexcept ->  Error& = default;
		auto operator=(Error &&rhs) noexcept -> Error& = default;


	private:

		[[nodiscard]] static auto toString(Code code) -> const char *;

		constexpr Error(const sl &loc) noexcept;



		static Error m_lastError;

		Code m_code;
		sl m_location;
	};
}