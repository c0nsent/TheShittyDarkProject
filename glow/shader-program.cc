#include "shader-program.hpp"

#include <glad/glad.h>

#include <stdexcept>
#include <utility>


namespace glow
{
	auto ShaderProgram::get(const InfoType info) const noexcept -> i32
	{
		i32 requested{};
		glGetProgramiv(m_id, std::to_underlying(info), &requested);
		return requested;
	}


	ShaderProgram::ShaderProgram(CreateInfo &&createInfo)
		: m_shaders{std::move(createInfo.vertexShader), std::move(createInfo.fragmentShader), std::move(createInfo.geometryShader)}
		, m_id{glCreateProgram()}
	{
		auto attachIfExist{[&] (const auto &shader) noexcept
		{
			if (not shader.isExists()) return;

			glAttachShader(m_id, shader.getId());
			shader.deleteShader();
		}};

		attachIfExist(std::get<VertexShader>(m_shaders));
		attachIfExist(std::get<FragmentShader>(m_shaders));
		attachIfExist(std::get<GeometryShader>(m_shaders));

		glLinkProgram(m_id);

		if (isLinked()) return;

		auto log{getInfoLog().value_or("No Log")};
		throw std::runtime_error{"Failed to link shader program: " + std::move(log)};
	}


	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_id);
	}


	auto ShaderProgram::getId() const noexcept -> u32
	{
		return m_id;
	}


	auto ShaderProgram::isLinked() const noexcept -> bool
	{
		return get(InfoType::LinkStatus);
	}


	auto ShaderProgram::getLogLength() const noexcept -> isize
	{
		return get(InfoType::InfoLogLength);
	}


	auto ShaderProgram::getInfoLog() const -> std::optional<std::string>
	{
		const auto infoLogLength{getLogLength()};

		if (infoLogLength == 0) return std::nullopt;

		char infoLog[infoLogLength];
		glGetProgramInfoLog(m_id, infoLogLength, nullptr, infoLog);

		return std::string{infoLog};
	}


	template<class T> requires std::derived_from<T, detail::BaseShader>
	auto ShaderProgram::hasAttachedShader() const noexcept  -> bool
	{
		return std::get<T>(m_shaders).isExists();
	}


	template<class T> requires std::derived_from<T, detail::BaseShader>
	auto ShaderProgram::getAttachedShader() const noexcept -> T &
	{
		return std::get<T>(m_shaders);
	}


	auto ShaderProgram::use() const noexcept -> void
	{
		glUseProgram(m_id);
	}
}
