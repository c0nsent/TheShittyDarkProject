#pragma once

#include "basic-types.hpp"

#include <tuple>

namespace glow
{
	class ClearBuffer
	{
		enum class Buffer : u16
		{
			Depth = 0x00000100,
			Stencil = 0x00000400,
			Color = 0x00004000,
		};

	public:

		ClearBuffer(std::tuple<Color> &&bufferValues) noexcept;

		void clear() const noexcept;

	private:

		Buffer m_clearBuffers;
	};
}