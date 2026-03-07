#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLOW_BASIC_TYPES_NO_NAMESPACE
#include "glow/core.hpp"
#include "glow/shader-program.hpp"
#include "glow/shader.hpp"


constexpr i32 WIDTH{800};
constexpr i32 HEIGHT{600};
constexpr auto TITLE{"The Shitty Dark Project"};


auto glCheckError_(const char *file, const i32 line) -> GLenum
{
	GLenum code{};

	while((code = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (code)
		{
			case GL_INVALID_ENUM:
				error = "INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				error = "INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				error = "INVALID_OPERATION";
				break;
			case GL_STACK_OVERFLOW:
				error = "STACK_OVERFLOW";
				break;
			case GL_STACK_UNDERFLOW:
				error = "STACK_UNDERFLOW";
				break;
			case GL_OUT_OF_MEMORY:
				error = "OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				error = "INVALID_FRAMEBUFFER_OPERATION";
				break;

			default:
				error = "UNKNOWN_ERROR";
		}

		std::cout << "Error " << error << " : " << line << " | " << error <<std::endl;
	}
	return code;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

auto errorCallback(const i32 error, const char *description) -> void
{
	std::cerr << "Error: " << error << " " << description << std::endl;
}

auto initGlfw(const i32 openglMajorVersion, const i32 openglMinorVersion, const bool isCoreProfile) -> void
{
	glfwSetErrorCallback(errorCallback);

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


auto parseShaderFile(const char* path) -> std::string
{
	std::ifstream file{path};
	std::ostringstream oss;
	oss << file.rdbuf();

	return oss.str();
}


auto main() -> int
{
	try
	{
		initGlfw(4, 6, true);

		auto window{createWindow(WIDTH, HEIGHT, TITLE)};

		initGlad();

		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		const glow::Shader vertexShader{glow::Shader::Type::Vertex, "shader.vert"};

		std::cerr << vertexShader.getInfoLog() << std::endl;

		const glow::Shader fragmentShader{ glow::Shader::Type::Fragment, "shader.frag" };


		const glow::ShaderProgram shaderProgram{vertexShader, fragmentShader};

		if (const std::string infoLog{shaderProgram.getInfoLog()}; not infoLog.empty())
		{
			std::cerr << infoLog << std::endl;
			return 1;
		}

		constexpr auto vertices{ std::to_array<f32>({
			-0.5f,  0.25f, 0.0f,
			0.5f, 0.25f, 0.0f,
			0.0f, -0.75f, 0.0f,

			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.f, 0.5f, 0.0f,
		})};

		constexpr auto indices{ std::to_array<u32>({
			0, 1, 2,
			3, 4, 5
		})};

		u32 vertexBufferObject, vertexArrayObj, elementBufferObj;
		glGenVertexArrays(1, &vertexArrayObj);
		glGenBuffers(1, &vertexBufferObject);
		glGenBuffers(1, &elementBufferObj);

		glBindVertexArray(vertexArrayObj);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices.front()), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObj);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices.front()), indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), static_cast<void *>(0));
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glCheckError();
		glBindVertexArray(0);
		glCheckError();

		while (not glfwWindowShouldClose(window))
		{
			processInput(window);

			glow::clearColor({0.2f, 0.3f, 0.3f});
			glClear(GL_COLOR_BUFFER_BIT);

			shaderProgram.use();
			glBindVertexArray(vertexBufferObject);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glDeleteVertexArrays(1, &vertexArrayObj);
		glDeleteBuffers(1, &vertexBufferObject);
		glDeleteBuffers(1, &elementBufferObj);

		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}