#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "basic-type-aliases.hpp"

using namespace sdp;

constexpr i32 WIDTH{800};
constexpr i32 HEIGHT{600};
constexpr auto TITLE{"The Shitty Dark Project"};

auto initGlfw(const i32 openglMajorVersion, const i32 openglMinorVersion, const bool isCoreProfile) -> void
{
	if (not glfwInit())
		throw std::runtime_error("GLFW could not be initialized");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openglMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openglMinorVersion);

	const i32 profile{isCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE};
	glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
}

[[nodiscard]] auto createWindow(const i32 width, const i32 height, const char *title ) ->  GLFWwindow *
{
	auto window{glfwCreateWindow(width, height, title, nullptr, nullptr)};
	if (not window)
		throw std::runtime_error("Failed to create GLFW window.");

	glfwMakeContextCurrent(window);

	return window;
}

auto initGlad() -> void
{
	if (not gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		throw std::runtime_error("Failed to initialize GLAD.");
}

auto framebufferSizeCallback(GLFWwindow *window, const i32 width, const i32 height) -> void
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void outputShaderCompilationStatus(const u32 shaderId)
{
	i32 infoLogLength{0};
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength == 0) return;

	std::string shaderTypeName{};
	i32 shaderType{0};
	glGetShaderiv(shaderId, GL_SHADER_TYPE, &shaderType);

	switch(shaderType)
	{
		case GL_VERTEX_SHADER:
			shaderTypeName = "Vertex";
			break;
		case GL_FRAGMENT_SHADER:
			shaderTypeName = "Fragment";
			break;
		case GL_GEOMETRY_SHADER:
			shaderTypeName = "Geometry";
			break;
		default:
			shaderTypeName = "Unknown";
	}

	char infoLog[infoLogLength];
	glGetShaderInfoLog(shaderId, infoLogLength, nullptr, infoLog);
		std::cerr << infoLog << std::endl;
		throw std::runtime_error{shaderTypeName + " shader compilation failed"};
}

auto main() -> int
{
	try
	{
		initGlfw(4, 6, true);

		auto window{createWindow(WIDTH, HEIGHT, TITLE)};

		initGlad();

		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		constexpr auto vertices{ std::to_array<f32>({
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
		})};


		u32 vertexBufferObject, vertexArrayObj ;
		glGenVertexArrays(1, &vertexArrayObj);
		glGenBuffers(1, &vertexBufferObject);
		glBindVertexArray(vertexArrayObj);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), vertices.data(), GL_STATIC_DRAW);

		constexpr auto vertexShaderSource{R"(
			#version 460 core
			layout (location=0) in vec3 aPos;

			void main()
			{
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
			}
		)"};

		const u32 vertexShader{glCreateShader(GL_VERTEX_SHADER)};
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);
		outputShaderCompilationStatus(vertexShader);

		constexpr auto fragmentShaderSource{R"(
			#version 460

			out vec4 FragColor;

			void main()
			{
				FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			}
		)"};

		const u32 fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);
		outputShaderCompilationStatus(fragmentShader);

		u32 shaderProgram{glCreateProgram()};
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		i32 infoLogSize{};
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogSize);
		if (infoLogSize != 0)
		{
			char infoLog[infoLogSize];
			glGetProgramInfoLog(shaderProgram, infoLogSize, nullptr, infoLog);
			std::cerr << infoLog << std::endl;
			return 1;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), static_cast<void *>(0));
		glEnableVertexAttribArray(0);

		while (not glfwWindowShouldClose(window))
		{
			processInput(window);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(shaderProgram);
			glBindVertexArray(vertexBufferObject);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glDeleteVertexArrays(1, &vertexArrayObj);
		glDeleteBuffers(1, &vertexBufferObject);
		glDeleteProgram(shaderProgram);

		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}