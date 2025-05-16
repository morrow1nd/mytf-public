#pragma once

#include "sgl_vertex_shader.hpp"
#include "sgl_fragment_shader.hpp"

#include "sglm.hpp"

class AppVertexShader : public sgl::VertexShaderBase {
protected:
    void Init() override {
        uniformModelIndex = RegisterUniformMat4("model");
        uniformViewIndex = RegisterUniformMat4("view");
        uniformProjectionIndex = RegisterUniformMat4("projection");

        inaPosId = RegisterInVec3("aPos");
        inaTexCoordId = RegisterInVec2("aTexCoord");

        outTexCoordId = RegisterOutVec2("TexCoord");
    }

    void MainFunc() override {
        const glm::mat4& projection = GetUniformMat4(uniformProjectionIndex);
        const glm::mat4& view = GetUniformMat4(uniformViewIndex);
        const glm::mat4& model = GetUniformMat4(uniformModelIndex);

        const glm::vec3& aPos = GetInVec3(inaPosId);

        gl_Position = projection * view * model * glm::vec4(aPos, 1.0f);

        const glm::vec2 aTexCoord = GetInVec2(inaTexCoordId);
        glm::vec2& TexCoord = GetOutVec2(outTexCoordId);
        TexCoord = aTexCoord;
    }

private:
    int uniformModelIndex;
    int uniformViewIndex;
    int uniformProjectionIndex;

    int inaPosId;
    int inaTexCoordId;

    int outTexCoordId;
};

class AppFragmentShader : public sgl::FragmentShaderBase {
protected:
    void Init() override {
        inTexCoordId = RegisterInVec2("TexCoord");

        uniformTexture1Id = RegisterUniformSampler2D("texture1");
        uniformTexture2Id = RegisterUniformSampler2D("texture2");

        //outFragColorId = RegisterOutVec4("FragColor");
    }

    void MainFunc() override {
        const glm::vec2 TexCoord = GetInVec2(inTexCoordId);

        output = glm::mix(texture(uniformTexture1Id, TexCoord), texture(uniformTexture2Id, TexCoord), 0.2f);
    }

private:
    int uniformTexture1Id;
    int uniformTexture2Id;
    int inTexCoordId;
    //int outFragColorId;
};
