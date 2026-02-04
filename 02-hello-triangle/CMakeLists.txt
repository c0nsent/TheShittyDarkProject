project(02-HelloTriangle
		LANGUAGES CXX C
)

set(SHADERS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADER_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

file(GLOB SHADERS
		${SHADER_SOURCE_DIR}/*.vert,
		${SHADER_SOURCE_DIR}/*.frag,
		${SHADER_SOURCE_DIR}/*.glsl
)

foreach(SHADER IN LISTS SHADERS)
	get_filename_component(SHADER_NAME ${SHADER})
	add_custom_command(
			OUTPUT ${SHADER_DEST_DIR}
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
	)

#TODO: Написать хуету которая будет сорсы шейдеров кидать в папку с экзешником
add_executable(02-HelloTriangle
		main.cpp
)

target_link_libraries(02-HelloTriangle
		glfw3
		glad
)