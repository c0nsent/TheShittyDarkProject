#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <iostream>


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
	{
		windowFiller = Color{1.0f, 0.0f, 0.5f, 1.0f};
	}
}



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

	const auto version{ reinterpret_cast<const char*>(glGetString(GL_VERSION)) };
	std::cout << "OpenGL version: " << version << std::endl;

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
	return 0;
}