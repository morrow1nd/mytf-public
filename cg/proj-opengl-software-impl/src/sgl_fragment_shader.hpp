#pragma once

#include <string>

#include "sgl_shader.hpp"
#include "sglm.hpp"

namespace sgl
{
    struct FragmentShaderRuntimeEnv : public ShaderRuntimeEnv
    {
        glm::vec4 output;
    };

    class FragmentShaderBase : public ShaderBase
    {
    public:
        virtual void Init() = 0;
        virtual void MainFunc(FragmentShaderRuntimeEnv& env) = 0;
    };
}
