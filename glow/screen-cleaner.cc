/**
 * @date 3/8/26
 * 
 * @author amitayus_
 */

#include "screen-cleaner.hpp"

namespace glow
{
	ClearBuffer::ClearBuffer(const std::tuple<Color> &bufferValues) noexcept
		: m_clearBuffers{Buffer::Color}
	{
		const auto [red, green, blue, alpha]{std::get<Color>(bufferValues)};
		glClearColor(red, green, blue, alpha);
	}


	void ClearBuffer::clear() const noexcept
	{
		glClear(static_cast<u32>(m_clearBuffers));
	}
}
