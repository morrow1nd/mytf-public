#pragma once

#include <vector>
#include "sgl_gpuprogram_runtime.hpp"
#include "sgl_shader.hpp"
#include "sgl_vertex_shader.hpp"
#include "sgl_fragment_shader.hpp"

namespace sgl
{
    struct GpuProgram
    {
        sgl::VertexShaderBase* vertexShader;
        sgl::FragmentShaderBase* fragShader;
        GpuProgramRuntimeEnv runtimeEnv;

        GpuProgram(sgl::VertexShaderBase* vertexShader, sgl::FragmentShaderBase* fragShader)
            : vertexShader(vertexShader), fragShader(fragShader)
        {
            vertexShader->Init();
            fragShader->Init();

            runtimeEnv.AddUniformNames(vertexShader->GetUniformName2Id());
            runtimeEnv.AddUniformNames(fragShader->GetUniformName2Id());
        }
    };
}
