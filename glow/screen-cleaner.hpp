#pragma once

#include "core.hpp"

#include <tuple>

namespace glow
{
	class ClearBuffer
	{
		enum class Buffer
		{
			Color = GL_COLOR_BUFFER_BIT,
			Depth = GL_DEPTH_BUFFER_BIT,
			Stencil = GL_STENCIL_BUFFER_BIT,
		};

	public:

		ClearBuffer(const std::tuple<Color> &bufferValues) noexcept;

		void clear() const noexcept;

	private:

		Buffer m_clearBuffers;
	};
}