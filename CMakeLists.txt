cmake_minimum_required(VERSION 4.2)

project(TheShittyDarkProject
		VERSION 0.0.1
		LANGUAGES CXX
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(external/glad)

add_executable(${PROJECT_NAME}
		main.cpp
)

target_link_libraries(${PROJECT_NAME}
		glfw3
		OpenGL::GL
		glad
)