#pragma once

#include "basic-types.hpp"


namespace glow
{
    class Uniform1f
    {
    public:

        Uniform1f(u32 shaderId, const char *name) noexcept;

        auto setValue(f32 val) const noexcept -> void;
        [[nodiscard]] auto value() const noexcept -> f32;

    private:

        const u32 m_shaderProgram;
        const i32 m_location;
    };
}
