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
using i32 = std::int32_t;
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

constexpr std::array triangleVertices {
	-0.5f, -0.5f, 0.f, 0.5f, -0.5f, 0.f, 0.0f, -0.5f, 0.f
};

constexpr auto vertexShaderSource{
	"#version 460 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0"
};

constexpr auto fragmentShaderSource{
	"#version 460 core\n"
	"out vec4 FragColor;\n"
	"void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f) }\n"
};

int main()
{
	//std::println("{}", sizeof(triangleVertices));
	u32 vertexBufferObj{};
	glGenBuffers(1, &vertexBufferObj);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);

	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices.data(), GL_STATIC_DRAW);

	const u32 vertexShader{ glCreateShader(GL_VERTEX_SHADER) };

	std::println("{}", vertexShader);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	i32 success{};
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (not success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::println("Блядь пиздец");
		std::println("{}",infoLog);

		return 1;
	}

	const u32 fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (not success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::println("{}", infoLog);
	}


}