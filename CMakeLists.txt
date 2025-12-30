cmake_minimum_required(VERSION 3.16)

project(TheShittyDarkProject
		VERSION 0.0.1
		LANGUAGES CXX C
)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Adjust path to your glad sources/headers
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(${PROJECT_NAME}
		main.cpp
)

include_directories(${GLEW_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

target_link_libraries(${PROJECT_NAME}
		glfw3
		OpenGL::GL
		${GLEW_LIBRARIES}
		glad
)