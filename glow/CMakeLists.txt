project(glow
		VERSION 0.0.1
		LANGUAGES CXX
		DESCRIPTION "OpenGL Lightweight Object Wrapper"
)

set(CMAKE_CXX_STANDARD 23)

add_library( glow SHARED
		core.hpp
		shader.cc shader.hpp
		shader-program.cc shader-program.hpp
		buffer.cc buffer.hpp
)

add_subdirectory(glad)

target_link_libraries(glow PUBLIC
		glad
)