cmake_minimum_required(VERSION 4.2)

project(Glad
		LANGUAGES C
)
add_library(Glad external/glad/src/glad.c)

project(TheShittyDarkProject
		VERSION 0.0.1
		LANGUAGES CXX
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

#[[include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include)
file(GLOB BUTTERFLIES_SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c)]]

add_executable(${PROJECT_NAME}
		main.cpp
		#${BUTTERFLIES_SOURCES_C}
)

target_link_libraries(${PROJECT_NAME}
		glfw3
		OpenGL::GL
		glad
)