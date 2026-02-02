#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cstdint>
#include <string>
#include <iostream>
#include <stdfloat>
#include <oneapi/tbb/info.h>

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using f16 = std::float16_t;
using f32 = std::float32_t;
using f64 = std::float64_t;

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

constexpr auto c_vertexShaderSource{
	"#version 460 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0"
};

constexpr auto с_fragmentShaderSource{
	"#version 460 core\n"
	"out vec4 FragColor;\n"
	"void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }\n"
};

void configGlfw(const u8 majorVersion=4, const u8 minorVersion=6, const bool isCoreProfile=true)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

	const i32 openglProfile{isCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE};

	glfwWindowHint(GLFW_OPENGL_PROFILE, openglProfile);
}

void shaderCompilationStatus(const u32 shaderId)
{
	i32 success{};
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	if (not success)
	{
		i32 logSize{};
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);
		char infoLog[logSize];
		glGetShaderInfoLog(shaderId, logSize, nullptr, infoLog);
		std::cerr << infoLog << std::endl;
	}}


void processInput(GLFWwindow *window)
{

}



int main()
{
	glfwSetErrorCallback(errorCallback);

	if (not glfwInit())
	{
		std::cerr << "Failed to initialize GLFW." << std::endl;
		return 1;
	}
	configGlfw();

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

	const auto version{ reinterpret_cast<const char*>(glGetString(GL_VERSION)) };
	std::cout << "OpenGL version: " << version << std::endl;

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	constexpr std::array vertices{ std::move(std::to_array<f32>({
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	}))};

	u32 vertexBufferObject{};
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), vertices.data(), GL_STATIC_DRAW);

	const u32 vertexShader{glCreateShader(GL_VERTEX_SHADER)};
	glShaderSource(vertexShader, 1, &c_vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	shaderCompilationStatus(vertexShader);

	const u32 fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
	glShaderSource(fragmentShader, 1, &с_fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	shaderCompilationStatus(fragmentShader);

	const u32 shaderProgram{glCreateProgram()};
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	i32 success{};
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (not success)
	{
		i32 logSize{};
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logSize);
		char infoLog[logSize];
		glGetProgramInfoLog(shaderProgram, logSize, nullptr, infoLog);
		std::cerr << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	const Color clearColor{ 1.0f, 1.0f, 1.0f, 1.0f };

	while (not glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(clearColor.red, clearColor.green, clearColor.blue, clearColor.alpha);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}