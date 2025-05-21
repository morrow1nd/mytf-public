#pragma once

#include "sgl_vertex_shader.hpp"
#include "sgl_fragment_shader.hpp"

#include "sglm.hpp"

class AppVertexShader : public sgl::VertexShaderBase
{
public:
    void Init() override
    {
        uniformModelIndex = RegisterUniformMat4("model");
        uniformViewIndex = RegisterUniformMat4("view");
        uniformProjectionIndex = RegisterUniformMat4("projection");

        outTexCoordId = RegisterOutVec2("TexCoord"); // todo
    }

    void MainFunc(sgl::VertexShaderRuntimeEnv& env) override
    {
        const glm::mat4& projection = env.GetUniformMat4(uniformProjectionIndex);
        const glm::mat4& view = env.GetUniformMat4(uniformViewIndex);
        const glm::mat4& model = env.GetUniformMat4(uniformModelIndex);

        const glm::vec3& aPos = env.GetLayoutVec3(0);

        // MVP矩阵的计算可以挪到app阶段
        env.gl_Position = projection * view * model * glm::vec4(aPos, 1.0f);

        const glm::vec2 aTexCoord = env.GetLayoutVec2(1);
        glm::vec2& TexCoord = env.GetOutVec2(outTexCoordId);

        TexCoord = aTexCoord;
    }

private:
    int uniformModelIndex = 0;
    int uniformViewIndex = 0;
    int uniformProjectionIndex = 0;

    int outTexCoordId = 0;
};

class AppFragmentShader : public sgl::FragmentShaderBase
{
public:
    void Init() override
    {
        inTexCoordId = RegisterInVec2("TexCoord"); // todo

        uniformTexture1Id = RegisterUniformSampler2D("texture1"); // todo
        uniformTexture2Id = RegisterUniformSampler2D("texture2");

        outFragColorId = RegisterOutVec4("FragColor");
    }

    void MainFunc(sgl::FragmentShaderRuntimeEnv& env) override
    {
        const glm::vec2 TexCoord = env.GetInVec2(inTexCoordId);

        glm::vec4& fragColor = env.GetOutVec4(outFragColorId);
        fragColor = glm::mix(env.texture(uniformTexture1Id, TexCoord), env.texture(uniformTexture2Id, TexCoord), 0.2f);
    }

private:
    int uniformTexture1Id = 0;
    int uniformTexture2Id = 0;
    int inTexCoordId = 0;
    int outFragColorId = 0;
};
