#include "shader.hpp"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <utility>

namespace glow
{
	namespace detail
	{
		auto BaseShader::get(const InfoType info) const noexcept -> i32
		{
			i32 requested;
			glGetShaderiv(m_id, std::to_underlying(info), &requested);

			return requested;
		}


		auto BaseShader::compile(const char *path) const -> void
		{
			std::ifstream file{path};

			if (not file.is_open())
				throw std::runtime_error{std::string{"Cannot open shader source file by path: "} + path};

			std::ostringstream oss;
			oss << file.rdbuf();
			const std::string src{oss.str()};
			auto cSrc{src.c_str()};

			glShaderSource(m_id, 1, &cSrc,  nullptr);
			glCompileShader(m_id);

			if (isCompiled()) return;

			auto log{getInfoLog().value_or("No log")};
			throw std::runtime_error{"Shader compilation failed: " + std::move(log)};
		}


		auto BaseShader::isMarkedForDeletion() const noexcept -> bool
		{
			return get(InfoType::DeleteStatus);
		}


		auto BaseShader::isCompiled() const noexcept -> bool
		{
			return get(InfoType::CompileStatus);
		}


		auto BaseShader::getInfoLogLength() const noexcept -> isize
		{
			return get(InfoType::InfoLogLength);
		}


		auto BaseShader::getSourceLength() const noexcept -> usize
		{
			return get(InfoType::SourceLength);
		}


		auto BaseShader::isExists() const noexcept -> bool
		{
			return m_id == NONE;
		}


		auto BaseShader::getId() const noexcept -> u32
		{
			return m_id;
		}


		auto BaseShader::getInfoLog() const -> std::optional<std::string>
		{
			const isize infoLogLength{getInfoLogLength()};

			if (infoLogLength == 0) return std::nullopt;

			std::string infoLog;
			glGetShaderInfoLog(m_id, infoLogLength, nullptr, infoLog.data());

			return std::make_optional(std::move(infoLog));
		}


		auto BaseShader::deleteShader() const noexcept -> void
		{
			glDeleteShader(m_id);
		}


		BaseShader::~BaseShader()
		{
			if (m_id != NONE) deleteShader();
		}


		BaseShader::BaseShader(BaseShader &&rhs) noexcept
		{
			m_id = rhs.m_id;
			rhs.m_id = NONE;
		}


		auto BaseShader::operator=(BaseShader &&rhs) noexcept -> BaseShader &
		{
			BaseShader{std::move(rhs)};

			return *this;
		}


		BaseShader::BaseShader(const ShaderType type) noexcept
			: m_id{glCreateShader(std::to_underlying(type))}
		{
		}
	}


	VertexShader::VertexShader(const char *srcPath)
		: BaseShader{ShaderType::Vertex}
	{
		compile(srcPath);
	}


	FragmentShader::FragmentShader(const char *srcPath)
		: BaseShader{ShaderType::Fragment}
	{
		compile(srcPath);
	}


	GeometryShader::GeometryShader(const char *srcPath)
	: BaseShader{ShaderType::Geometry}
	{
		compile(srcPath);
	}
}
