#include <iostream>
#include <memory>
#include <stdexcept>

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

auto main() -> int
{
	try
	{
		initGlfw(4, 6, true);

		auto window{createWindow(WIDTH, HEIGHT, TITLE)};

		initGlad();

		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		while (not glfwWindowShouldClose(window))
		{
			processInput(window);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}