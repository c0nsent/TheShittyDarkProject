#include "utility.hpp"

#include <iostream>

namespace glow
{


	auto Error::checkAndPrint(sl &&loc) -> void
	{
		const Error error{loc};

		if (error.m_code == Code::NoError) return;

		std::cerr << loc.file_name() << " " << loc.function_name() << " "  << loc.line() << " "
				  << "Error :" << toString(error.m_code);
	}


	auto Error::hasError(sl &&loc) noexcept -> bool
	{
		m_lastError = {loc};

		return m_lastError.m_code == Code::NoError;
	}


	auto Error::code() const noexcept -> Code
	{
		return m_code;
	}


	auto Error::location() const noexcept -> sl
	{
		return m_location;
	}



	auto Error::check(sl &&loc) -> std::tuple<Code, sl>
	{
		const auto code{static_cast<Code>(glGetError())};

		return {code, loc};
	}


	auto Error::toString(const Code code) -> const char *
	{
		static const std::unordered_map<Code, const char *> codeStrings
		{
			{Code::InvalidEnum, "Invalid enum"},
			{Code::InvalidValue, "Invalid value"},
			{Code::InvalidOperation, "Invalid operation"},
			{Code::StackOverflow, "Stack overflow"},
			{Code::StackUnderflow, "Stack underflow"},
			{Code::OutOfMemory, "Out of memory"},
			{Code::InvalidFrameBufferOperation, "Invalid framebuffer operation"}
		};

		return codeStrings.at(code);
	}


	constexpr Error::Error(const sl &loc) noexcept : m_code{static_cast<Code>(glGetError())}, m_location{loc} {}

}
