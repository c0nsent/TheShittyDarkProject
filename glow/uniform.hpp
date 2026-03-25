#pragma once

#include "basic-types.hpp"
#include "shader-program.hpp"

#include <glad/glad.h>

#include <type_traits>


namespace glow
{
    class Uniform1f
    {
        friend class ShaderProgram;

    public:

        auto setValue(f32 val) const noexcept -> void;
        auto value() const noexcept -> f32;



    private:

        explicit Uniform1f(u32 shaderId, const char *name) noexcept;

        const u32 m_shaderId;
        const i32 m_id;
    };
}
