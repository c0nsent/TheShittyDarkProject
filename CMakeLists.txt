cmake_minimum_required(VERSION 4.2)

project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(external/glad)

add_executable(01-CreatingWindow
		01-creating-window.cpp
)

target_link_libraries(01-CreatingWindow
		glfw3
		glad
)

add_subdirectory(02-hello-triangle)

