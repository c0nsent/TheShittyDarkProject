cmake_minimum_required(VERSION 4.2)

project(TheShittyDarkProject
		LANGUAGES CXX C
		VERSION 0.0.2
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 3.5 REQUIRED)
find_package(glm 1.0.3 REQUIRED)
find_package(Boost 1.89 REQUIRED)

add_subdirectory(glow)

add_executable(${PROJECT_NAME}
		main.cc
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_CURRENT_SOURCE_DIR}/shaders
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
		COMMENT "Копирование шейдеров в выходную директорию"
)

target_link_libraries(${PROJECT_NAME}
		glfw3
		glow
)