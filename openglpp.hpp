#pragma once

#include <glad/glad.h>

namespace gl
{
	class Shader
	{
	public:

		class Type
		{
		public:
			enum class Values
			{
				Vertex = GL_VERTEX_SHADER,
				Fragment = GL_FRAGMENT_SHADER,
				Geometry = GL_GEOMETRY_SHADER,
			};

			using enum Values;

			void foo()
			{
				Vertex;
			}
		};

		Shader::Type get()
		{
			return Type::Geometry;
		}


	};
}