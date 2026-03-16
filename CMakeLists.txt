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

file(GLOB_RECURSE SHADER_FILES "shaders/*")
add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders_stamp
		DEPENDS ${SHADER_FILES}
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
		COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/shaders_stamp
		COMMENT "Копирование шейдеров при изменении"
)
add_custom_target(copy_shaders DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/shaders_stamp)
add_dependencies(${PROJECT_NAME} copy_shaders)

target_link_libraries(${PROJECT_NAME}
		glfw3
		glow
)