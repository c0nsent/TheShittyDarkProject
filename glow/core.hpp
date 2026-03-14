#pragma once

#include <glad/glad.h>

#include <expected>
#include <boost/optional.hpp>


namespace glow
{
	namespace basic_types
	{

		using f16 = _Float16;
		using f32 = _Float32;
		using f64 = _Float64;
		using f128 = _Float128;

		using u8 = unsigned char;
		using u16 = unsigned short int;
		using u32 = unsigned int;
		using u64 = unsigned long int;

		using i8 = signed char;
		using i16 = signed short int;
		using i32 = signed int;
		using i64 = signed long int;

		using usize = u32;
		using isize = i32;

		using b32 = i32;


		template <typename T>
		using result = std::expected<T, const char *>;

		template <typename T>
		using opt = boost::optional<T>;
	}

	using namespace glow::basic_types;

	static constexpr usize SHADER_TYPE_COUNT{3};

	struct Color
	{
		f32 red{};
		f32 green{};
		f32 blue{};
		f32 alpha{1.f};
	};

	inline auto clearColor(const Color &background) noexcept -> void
	{
		glClearColor(background.red, background.green, background.blue, background.alpha);
	}
}
