#include "error.hpp"

#include <iostream>

namespace glow
{
	auto Error::last() noexcept -> Code
	{
		return static_cast<Code>(glGetError());
	}


	auto Error::print(const Code code, const std::source_location &loc) -> void
	{
		if (code == Code::NoError) return;

		std::cerr << "[ " <<  loc.file_name() << " | " << loc.function_name() << " | " << loc.line()
				  << " ] Error : " << toString(code) << '\n';
	}


	auto Error::toString(const Code code) -> const char *
	{
		switch (code)
		{
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
