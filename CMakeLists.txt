cmake_minimum_required(VERSION 4.2)

project(TheShittyDarkProject
		LANGUAGES CXX
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

#[[find_path(STB_INCLUDE_DIR stb_image.h)
if(STB_INCLUDE_DIR)
	target_include_directories(${PROJECT_NAME} PRIVATE ${STB_INCLUDE_DIR})
else()
	message(FATAL_ERROR "stb not found")
endif()]]

find_path(STB_INCLUDE_DIR
		NAMES stb_image.h          # ищем любой характерный заголовок
		PATH_SUFFIXES stb          # иногда stb_image.h лежит в подпапке stb/
)

if(NOT STB_INCLUDE_DIR)
	message(FATAL_ERROR "stb headers not found. Please install stb (e.g., 'sudo pacman -S stb')")
endif()

# Создаём интерфейсную цель для удобного подключения
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${STB_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
		glfw3
		glm
		glow
		stb
)