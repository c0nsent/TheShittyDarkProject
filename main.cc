#include <array>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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


auto framebufferSizeCallback(GLFWwindow *window, const i32 width, const i32 height) -> void
{
	glow::viewport(0, 0, width, height);
}


auto processInput(GLFWwindow *window) -> void
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


auto main() -> int
{
	glfwSetErrorCallback(errorCallback);

	if (not glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window{glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr)};
	if (window == nullptr)
	{
		std::cerr << "Failed to create window\n";
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (not gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Failed to initialize GLAD.\n";
		return 1;
	}

	const glow::ShaderProgram shaderProgram{
		{glow::Shader::Type::Vertex, "shaders/shader.vert"},
		{glow::Shader::Type::Fragment, "shaders/shader.frag"}
	};

	if (not shaderProgram.isLinked())
	{
		std::cerr << shaderProgram.getInfoLog();
		return 1;
	}


	constexpr auto vertices{ std::to_array<f32>({
		-0.5f,  0.25f, 0.0f,
		0.5f, 0.25f, 0.0f,
		0.0f, -0.75f, 0.0f,
	})};

	u32 vbo;
	glGenBuffers(1, &vbo);
	u32 vao;
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glNamedBufferData(vbo, vertices.size() * sizeof(vertices.front()), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(f32), nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (not glfwWindowShouldClose(window))
	{
		processInput(window);

		const glow::ClearBuffer clearBuffer{std::make_tuple(glow::Color{0.2f, 0.3f, 0.3f})};
		clearBuffer.clear();

		const f32 greenValue{static_cast<f32>(glm::sin(glfwGetTime()) / 2.f + 0.5f)};
		const i32 vertexColor{glGetUniformLocation(shaderProgram.getId(), "ourColor")};
		shaderProgram.use();
		glUniform4f(vertexColor, 0.f, greenValue, 0.f, 1.f);

		glBindVertexArray(vao);
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