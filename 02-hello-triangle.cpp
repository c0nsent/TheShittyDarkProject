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
#include <iostream>


using f32 = std::float32_t;
using i32 = std::int32_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;

constexpr u16 c_width{ 640 };
constexpr u16 c_height{ 480 };

struct Color
{
	float red, green, blue, alpha;
};

void errorCallback(const i32 error, const char *description)
{
	std::cerr << "Error: "  << error << " - " << description << std::endl;
}

void framebufferSizeCallback(GLFWwindow *window, const i32 width, const i32 height)
{
	glViewport(0, 0, width, height);
}

void configGlfw(const u8 majorVersion, const u8 minorVersion, const bool isCoreProfile)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

	const auto openglProfile{isCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE};

	glfwWindowHint(GLFW_OPENGL_PROFILE, openglProfile);
}

void processInput(GLFWwindow *window, Color &windowFiller)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		windowFiller = Color{1.0f, 0.0f, 0.5f, 1.0f};
}

constexpr std::array triangleVertices {
	-0.5f, -0.5f, 0.f, 0.5f, -0.5f, 0.f, 0.0f, -0.5f, 0.f
};

void printVertexCompileStatus(const u32 vertexShaderId, const std::string_view logInfo, const i32 compileStatus)
{
	if (not compileStatus)
	{
		glGetShaderInfoLog(vertexShaderId, logInfo.size(), nullptr, reinterpret_cast<GLchar *>(logInfo.data()));
		std::println("Блядь пиздец");
		std::println("{}",infoLog);
	}
}

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
	glfwSetErrorCallback(errorCallback);

	if (not glfwInit())
	{
		std::cerr << "Failed to initialize GLFW." << std::endl;
		return 1;
	}
	configGlfw(4, 6, true);

	const auto window{glfwCreateWindow(c_width, c_height, "This Charming Man", nullptr, nullptr)};
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	if (not gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Failed to initialize GLAD." << std::endl;
		return 1;
	}

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

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	while (not glfwWindowShouldClose(window))
	{
		Color windowFiller{0.2f, 0.3f, 0.3f, 1.0f};
		processInput(window, windowFiller);

		glClearColor(windowFiller.red, windowFiller.green, windowFiller.blue, windowFiller.alpha);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}