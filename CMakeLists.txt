cmake_minimum_required(VERSION 4.2)

project(TheShittyDarkProject
		LANGUAGES CXX C
		VERSION 0.0.1
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(glow)

add_executable(${PROJECT_NAME}
		main.cc
)

target_link_libraries(${PROJECT_NAME}
		glfw3
		glow
)

