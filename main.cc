#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "glow/basic-types.hpp"
#include "glow/error.hpp"
#include "glow/screen-cleaner.hpp"
#include "glow/shader-program.hpp"
#include "glow/shader.hpp"
#include "glow/utility.hpp"

#include <array>
#include <iostream>

#include "glow/uniform.hpp"


using namespace glow::basicTypes;

constexpr i32 WIDTH{800};
constexpr i32 HEIGHT{600};
constexpr auto TITLE{"The Shitty Dark Project"};

auto errorCallback(const i32 error, const char *description) -> void
{
	std::cerr << "Error: " << error << " " << description << std::endl;
}


auto framebufferSizeCallback(GLFWwindow *, const i32 width, const i32 height) -> void
{
	glow::viewport(0, 0, width, height);
}


auto processInput(GLFWwindow *window) -> void
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);


}


auto createTexture(const char *path) -> u32
{
	u32 textureId;
	glGenTextures(1, &textureId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	i32 width, height, nrChannels;
	u8 *imageData{stbi_load(path, &width, &height, &nrChannels, 0)};

	const i32 format{nrChannels == 3 ? GL_RGB : GL_RGBA};

	if (not imageData)
		throw std::runtime_error{"Failed to load image\n"};

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageData);

	return textureId;
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

	const glow::ShaderProgram shaderProgram{std::make_tuple(
		glow::VertexShader{"shaders/shader.vert"},
		glow::FragmentShader{"shaders/shader.frag"},
		glow::GeometryShader{}
	)};

	constexpr auto vertices{ std::to_array<f32>({
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	2.0f, 2.0f,
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	2.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 2.0f,
	})};

	constexpr auto indices{ std::to_array<u32>({
		0, 1, 3,
		1, 2, 3,
	})};

	stbi_set_flip_vertically_on_load(true);

    glow::Error::printIfError();

	const auto containerTexture{createTexture("textures/container.png")};
	const auto obamaTexture{createTexture("textures/obama.png")};

    glow::Error::printIfError();

	u32 vbo, vao, ebo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);

    glow::Error::printIfError();

	glBindVertexArray(vao);

    glow::Error::printIfError();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glNamedBufferData(vbo, vertices.size() * sizeof(vertices.front()), vertices.data(), GL_STATIC_DRAW);

    glow::Error::printIfError();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glNamedBufferData(ebo, indices.size() * sizeof(indices.front()), indices.data(), GL_STATIC_DRAW);

    glow::Error::printIfError();

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(indices.front()), reinterpret_cast<void *>(0));
	glEnableVertexAttribArray(0);

    glow::Error::printIfError();

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(indices.front()), reinterpret_cast<void*>(3 * sizeof(indices.front())));
	glEnableVertexAttribArray(1);

    glow::Error::printIfError();

	glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(indices.front()), reinterpret_cast<void *>(6 * sizeof(indices.front())));
	glEnableVertexAttribArray(2);

    glow::Error::printIfError();
	shaderProgram.use();
    //shaderProgram.getUniform1f("texture1").setValue(0);
	//glUniform1i(glGetUniformLocation(shaderProgram.getId(), "texture1"), 0);

    shaderProgram.getUniform1f("texture2").setValue(1);

    glow::Error::printIfError();

	while (not glfwWindowShouldClose(window))
	{
		processInput(window);

		const glow::ClearBuffer clearBuffer{std::make_tuple(glow::Color{0.2f, 0.3f, 0.3f})};
		clearBuffer.clear();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, containerTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, obamaTexture);

		shaderProgram.use();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glow::Error::printIfError();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*glDeleteVertexArrays(1, &vertexArrayObj);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &elementBufferObj);*/

	glfwDestroyWindow(window);
	glfwTerminate();
}