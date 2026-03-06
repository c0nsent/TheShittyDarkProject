#pragma once

#include <cstdint>
#include <stdfloat>

#include "glad/glad.h"

#ifdef GLOW_BASIC_TYPES_NO_NAMESPACE

using f16 = std::float16_t;
using f32 = std::float32_t;
using f64 = std::float64_t;
using f128 = std::float128_t;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

#endif

namespace glow
{
	using f16 = std::float16_t;
	using f32 = std::float32_t;
	using f64 = std::float64_t;
	using f128 = std::float128_t;

	using u8 = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	using i8 = std::int8_t;
	using i16 = std::int16_t;
	using i32 = std::int32_t;
	using i64 = std::int64_t;


	static constexpr i32 True{GL_TRUE};
	static constexpr i32 False{GL_FALSE};

	struct Color
	{
		f32 red;
		f32 green;
		f32 blue;
		f32 alpha{1.f};
	};


	inline auto clearColor(const Color &background) noexcept -> void
	{
		glClearColor(background.red, background.green, background.blue, background.alpha);
	}
}
