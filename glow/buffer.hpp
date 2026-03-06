#pragma once

#include <array>

#include "core.hpp"


namespace glow
{
	class Buffer
	{

	public:

		enum class Type;

		template<class T, std::size_t Size>
		Buffer(Type type, const std::array<T, Size> &data);


	private:

		u32 m_id;
	};

	enum class Buffer::Type
	{
		ArrayBuffer = GL_ARRAY_BUFFER,
		ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
	};
}