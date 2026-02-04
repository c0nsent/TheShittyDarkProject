#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <stdfloat>

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using f16 = std::float16_t;
using f32 = std::float32_t;
using f64 = std::float64_t;

constexpr u16 c_width{640};
constexpr u16 c_height{480};

struct Color
{
	f32 red;
	f32 green;
	f32 blue;
	f32 alpha;
};

void errorCallback(const i32 error, const char *description)
{
	std::cerr << "Error: " << error << " - " << description << std::endl;
}


void framebufferSizeCallback(GLFWwindow *window, const i32 width, const i32 height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {}

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


void configGlfw(const u8 majorVersion = 4, const u8 minorVersion = 6, const bool isCoreProfile = true)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

	const i32 openglProfile{isCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE};

	glfwWindowHint(GLFW_OPENGL_PROFILE, openglProfile);
}


void shaderCompilationStatus(const u32 shaderId)
{
	const auto infoLogLength{ std::invoke(
		[&shaderId]
		{
			i32 result{};
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &result);
			return result;
		}
	)};

	if(infoLogLength != 0)
	{
		std::cerr << "Shader compilation failed." << std::endl;
		char infoLog[infoLogLength];
		glGetShaderInfoLog(shaderId, infoLogLength, nullptr, infoLog);
		std::cerr << infoLog << std::endl;
	}
}

void programCompilationStatusOutput(const u32 shaderId)
{
	const i32 infoLogLength{ std::invoke([&shaderId]
	{
		i32 length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		return length;
	})};

	if(infoLogLength != 0)
	{
		std::cout << "Shader program linking failed." << std::endl;
		char infoLog[512];
		glGetProgramInfoLog(shaderId, 512, nullptr, infoLog);
		std::cerr << infoLog << std::endl;
	}
}


int main()
{
	glfwSetErrorCallback(errorCallback);

	if(not glfwInit())
	{
		std::cerr << "Failed to initialize GLFW." << std::endl;
		return 1;
	}
	configGlfw();

	auto window{glfwCreateWindow(c_width, c_height, "This Charming Man", nullptr, nullptr)};
	if(window == nullptr)
	{
		std::cerr << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if(not gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Failed to initialize GLAD." << std::endl;
		return 1;
	}

	const auto version{reinterpret_cast<const char *>(glGetString(GL_VERSION))};
	std::cout << "OpenGL version: " << version << std::endl;

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

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	constexpr std::array vertices{
		std::to_array<f32>({
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		})
	};

	u32 vertexBufferObject{};
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), vertices.data(), GL_STATIC_DRAW);

	u32 vertexArrayObject{};
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), static_cast<void *>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	const Color clearColor{0.2f, 0.3f, 0.3f, 1.0f};

	while(not glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(clearColor.red, clearColor.green, clearColor.blue, clearColor.alpha);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}
