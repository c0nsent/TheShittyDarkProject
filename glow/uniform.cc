#include "uniform.hpp"

namespace glow
{
    auto Uniform1f::setValue(const f32 val) const noexcept -> void
    {
        glUniform1f(m_id, val);
    }

    auto Uniform1f::value() const noexcept -> f32
    {
        f32 value;
        glGetUniformfv(m_shaderId, m_id, &value);
        return value;
    }

    Uniform1f::Uniform1f(const u32 shaderId, const char *name) noexcept
    : m_shaderId{shaderId}
    , m_id{glGetUniformLocation(shaderId, name)}
    {
    }
}
