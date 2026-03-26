#include "uniform.hpp"

#include <glad/glad.h>


namespace glow
{
    Uniform1f::Uniform1f(const u32 shaderId, const char *name) noexcept
        : m_shaderProgram{shaderId}
          , m_location{glGetUniformLocation(shaderId, name)}
    {
    }

    auto Uniform1f::setValue(const f32 val) const noexcept -> void
    {
        glUniform1f(m_location, val);
    }

    auto Uniform1f::value() const noexcept -> f32
    {
        f32 value;
        glGetUniformfv(m_shaderProgram, m_location, &value);
        return value;
    }
}
