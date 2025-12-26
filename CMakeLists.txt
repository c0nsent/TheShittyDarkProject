cmake_minimum_required(VERSION 4.2)

project(TheShittyDarkProject
		VERSION 0.0.1
		LANGUAGES CXX C
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
		glad.h glad.c
		main.cpp
)

target_link_libraries(${PROJECT_NAME}
		glfw3
		OpenGL::GL
)
