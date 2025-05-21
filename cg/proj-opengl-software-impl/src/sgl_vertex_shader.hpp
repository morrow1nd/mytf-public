#pragma once

#include <string>
#include "sgl_base.hpp"
#include "sglm.hpp"
#include "sgl_shader.hpp"
#include "sgl_ds.hpp"

namespace sgl
{
    class VertexShaderRuntimeEnv : public ShaderRuntimeEnv
    {
    private:
        void* data = nullptr;
        int vertexIndex = -1;
        sgl::VertexArray* VAO = nullptr;
        sgl::Buffer* VBO = nullptr;
        
    public:
        void SetBuffer(sgl::VertexArray* VAO, sgl::Buffer* VBO)
        {
            this->VAO = VAO;
            this->VBO = VBO;
        }

        void SetVertexIndex(int index)
        {
            vertexIndex = index;
        }

        const glm::vec3& GetLayoutVec3(int layoutLocation)
        {
            const auto& attr = VAO->attribPointers[layoutLocation];
            ASSERT(attr.size == 3, "GetLayoutVec3 fail, attr.size != 3");
            ASSERT(attr.type == GL_FLOAT);
            ASSERT(attr.normalized == GL_FALSE); // 暂时只支持FALSE

            ASSERT(this->vertexIndex >= 0);
            const char* ptr = ((const char*)VBO->data) + (int)attr.pointer + attr.stride * this->vertexIndex;

            return * (const glm::vec3*)ptr;
        }

        const glm::vec2& GetLayoutVec2(int layoutLocation)
        {
            const auto& attr = VAO->attribPointers[layoutLocation];
            ASSERT(attr.size == 2, "GetLayoutVec2 fail, attr.size != 2");
            ASSERT(attr.type == GL_FLOAT);
            ASSERT(attr.normalized == GL_FALSE); // 暂时只支持FALSE

            ASSERT(this->vertexIndex >= 0);
            const char* ptr = ((const char*)VBO->data) + (int)attr.pointer + attr.stride * this->vertexIndex;

            return *(const glm::vec2*)ptr;
        }

        glm::vec4 gl_Position;
    };

    class VertexShaderBase : public ShaderBase
    {
    public:
        virtual void Init() = 0;
        virtual void MainFunc(VertexShaderRuntimeEnv& env) = 0;
    };
}
