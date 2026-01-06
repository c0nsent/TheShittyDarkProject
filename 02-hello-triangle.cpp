/**
 * @date 06.01.2026
 * 
 * @author amitayus_
 */


#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <array>
#include <stdfloat>
#include <cstdint>
#include <print>

using f32 = std::float32_t;
using u32 = std::uint32_t;

struct Vertex
{
	f32 x{};
	f32 y{};
	static constexpr f32 z{0.f};
};

/*constexpr std::array<Vertex, 3> triangleVertices {{
	{.x = -0.5f, .y = -0.5f}, {.x=0.5f, .y=-0.5f}, {.x=0.0f, .y=-0.5f}
}};*/

constexpr std::array triangleVertices{
	-0.5f, -0.5f, 0.f, 0.5f, -0.5f, 0.f, 0.0f, -0.5f, 0.f
};

int main()
{
	u32 vertexBufferObj{};
	glGenBuffers(1, &vertexBufferObj);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);

	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices.data()), triangleVertices.data(), GL_STATIC_DRAW);
}