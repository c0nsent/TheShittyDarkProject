project(glow
		VERSION 0.0.2
		LANGUAGES CXX
		DESCRIPTION "OpenGL Lightweight Object Wrapper"
)

set(CMAKE_CXX_STANDARD 23)

add_library( glow SHARED
		basic-types.hpp
		shader.cc shader.hpp
		shader-program.cc shader-program.hpp
		buffer.cc buffer.hpp
		loader.cc loader.hpp
		screen-cleaner.cc screen-cleaner.hpp
		error.cc error.hpp
		utility.cc utility.hpp
		uniform.cc uniform.hpp
		texture.cc texture.hpp
)

add_subdirectory(glad)

target_link_libraries(glow PUBLIC
		glad
		Boost::headers
)
