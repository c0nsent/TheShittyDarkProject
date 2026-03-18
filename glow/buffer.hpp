#pragma once

#include <array>

#include "core.hpp"

//TODO: Добавить проверку размера входного массива на делимость без остатотка на страйд

namespace glow
{
	namespace detail
	{
		class BaseBuffer
		{
		protected:

			enum class Type : u16
			{
				ArrayBuffer = GL_ARRAY_BUFFER,
				ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
			};

			template<class T, std::size_t Size>
			BaseBuffer(Type type, const std::array<T, Size> &data);

			u32 m_id;
		};
	}


}