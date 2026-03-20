#include "error.hpp"

#include <glad/glad.h>

#include <print>


namespace glow
{
	auto Error::last() noexcept -> Code
	{
		return static_cast<Code>(glGetError());
	}


	auto Error::print(const srcLoc loc) noexcept -> void
	{
		print(last(), loc);
	}


	auto Error::printIfError(const srcLoc loc) -> void
	{
		if (const Code code{last()}; code != Code::NoError) print(code, loc);
	}


	auto Error::print(const Code code, const srcLoc loc) -> void
	{
		std::println("[ {0} | {1} ] Error : {2}", loc.file_name(), loc.function_name(), toString(code));
	}


	auto Error::toString(const Code code) -> const char *
	{
		switch (code)
		{
			case Code::NoError: return "No error";
			case Code::InvalidEnum: return "Invalid enum";
			case Code::InvalidValue: return "Invalid value";
			case Code::InvalidOperation: return "Invalid operation";
			case Code::StackOverflow: return "Stack overflow";
			case Code::StackUnderflow: return "Stack underflow";
			case Code::OutOfMemory: return "Out of memory";
			case Code::InvalidFrameBufferOperation: return "Invalid frame buffer operation";

			default: return "Unknown error";
		}
	}
}
