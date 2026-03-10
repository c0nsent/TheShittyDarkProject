#include <array>
#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLOW_BASIC_TYPES_NO_NAMESPACE
#include "glow/core.hpp"
#include "glow/error.hpp"
#include "glow/screen-cleaner.hpp"
#include "glow/shader-program.hpp"
#include "glow/shader.hpp"


constexpr i32 WIDTH{800};
constexpr i32 HEIGHT{600};
constexpr auto TITLE{"The Shitty Dark Project"};

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


auto main() -> int
{
	try
	{
		initGlfw(4, 6, true);

		auto window{createWindow(WIDTH, HEIGHT, TITLE)};

		initGlad();

		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		const glow::Shader vertexShader{glow::Shader::Type::Vertex, "shader1.vert"};
		const glow::Shader fragmentShader1{glow::Shader::Type::Fragment, "shader1.frag"};
		const glow::Shader fragmentShader2{glow::Shader::Type::Fragment, "shader2.frag"};

		const glow::ShaderProgram shaderProgram1{vertexShader, fragmentShader1};
		const glow::ShaderProgram shaderProgram2{vertexShader, fragmentShader2};
		glow::Error::printIfError();

		constexpr auto vertices1{ std::to_array<f32>({
			-0.5f,  0.25f, 0.0f,
			0.5f, 0.25f, 0.0f,
			0.0f, -0.75f, 0.0f,
		})};

		constexpr auto vertices2{ std::to_array<f32>({
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.f, 0.5f, 0.0f,
		})};

		std::pair<u32, u32> vbo;
		glGenBuffers(2, &vbo.first);
		std::pair<u32, u32> vao;
		glGenVertexArrays(2, &vao.first);

		glBindVertexArray(vao.first);
		glBindBuffer(GL_ARRAY_BUFFER, vbo.first);
		glNamedBufferData(vbo.first, vertices1.size() * sizeof(vertices1.front()), vertices1.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, glow::FALSE, 3 * sizeof(f32), static_cast<void *>(0));
		glEnableVertexAttribArray(0);

		glBindVertexArray(vao.second);
		glBindBuffer(GL_ARRAY_BUFFER, vbo.second);
		glNamedBufferData(vbo.second, vertices2.size() * sizeof(vertices2.front()), vertices2.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, glow::FALSE, 3 * sizeof(f32), static_cast<void *>(0));
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		while (not glfwWindowShouldClose(window))
		{
			processInput(window);

			const glow::ClearBuffer clearBuffer{std::make_tuple(glow::Color{0.2f, 0.3f, 0.3f})};
			clearBuffer.clear();

			shaderProgram1.use();
			glBindVertexArray(vao.first);
			glow::Error::print();
			glDrawArrays(GL_TRIANGLES, 0, 3);

			shaderProgram2.use();
			glBindVertexArray(vao.second);
			glow::Error::print();
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		/*glDeleteVertexArrays(1, &vertexArrayObj);
		glDeleteBuffers(1, &vertexBufferObject);
		glDeleteBuffers(1, &elementBufferObj);*/

		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}