cmake_minimum_required(VERSION 4.2)

project(TheShittyDarkProject
		VERSION 0.0.1
		LANGUAGES CXX
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

#[[include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include)
file(GLOB BUTTERFLIES_SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c)]]

include_directories(SYSTEM "external/glad/include")

add_executable(${PROJECT_NAME}
		main.cpp
		"external/glad/src/glad.c"
		#${BUTTERFLIES_SOURCES_C}
)

target_link_libraries(${PROJECT_NAME}
		glfw3
		OpenGL::GL
)