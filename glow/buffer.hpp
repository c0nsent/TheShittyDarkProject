#pragma once

#include <array>

#include "basic-types.hpp"
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
				ArrayBuffer = 0x8892,
				ElementArrayBuffer = 0x8893,
			};

			template<class T, std::size_t Size>
			BaseBuffer(Type type, const std::array<T, Size> &data);

			u32 m_id;
		};


	}


}