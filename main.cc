#include <array>
#include <expected>
#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glow/core.hpp"
#include "glow/error.hpp"
#include "glow/screen-cleaner.hpp"
#include "glow/shader-program.hpp"
#include "glow/shader.hpp"
#include "glow/utility.hpp"


using namespace glow::basic_types;

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

[[nodiscard]] auto createWindow(const i32 width, const i32 height, const char *title ) noexcept
	-> std::expected<GLFWwindow *, const char *>
{
	auto window{glfwCreateWindow(width, height, title, nullptr, nullptr)};
	if (not window)
		return std::unexpected{"Failed to create GLFW window."};

	glfwMakeContextCurrent(window);

	return window;
}


auto framebufferSizeCallback(GLFWwindow *window, const i32 width, const i32 height) -> void
{
	glow::viewport(0, 0, width, height);
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

		GLFWwindow *window;

		if (auto expected{createWindow(WIDTH, HEIGHT, TITLE)}; expected.has_value())
			window = expected.value();
		else
		{
			std::cerr << "Error: " << expected.error() << '\n';
			return 1;
		}

		if (not gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			std::cerr << "Failed to initialize GLAD." << '\n';
			return 1;
		}

		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		const glow::Shader vertexShader{glow::Shader::Type::Vertex, "shaders/shader1.vert"};
		const glow::Shader fragmentShader1{glow::Shader::Type::Fragment, "shaders/shader1.frag"};

		const glow::ShaderProgram shaderProgram1{vertexShader, fragmentShader1};

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

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(f32), nullptr);
		glEnableVertexAttribArray(0);

		glBindVertexArray(vao.second);
		glBindBuffer(GL_ARRAY_BUFFER, vbo.second);
		glNamedBufferData(vbo.second, vertices2.size() * sizeof(vertices2.front()), vertices2.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(f32),nullptr);
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

			shaderProgram1.use();

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