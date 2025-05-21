#pragma once

#include "sgl_base.hpp"
#include "sglad.h"
#include <vector>
#include "sgl_shader.hpp"
#include "sgl_vertex_shader.hpp"
#include "sgl_fragment_shader.hpp"

namespace sgl
{
    struct Color
    {
        union
        {
            struct { float r, g, b, a; };
        };

        // todo: default constructor
    };

    struct ColorBuffer
    {
        Color* data;

        ColorBuffer(int width, int height)
        {
            data = new Color[width * height];
        }

        ~ColorBuffer()
        {
            delete[] data;
        }
    };

    struct DepthBuffer
    {
        float* data;

        DepthBuffer(int width, int height)
        {
            data = new float[width * height];
        }

        ~DepthBuffer()
        {
            delete[] data;
        }
    };

    struct VertexAttribPointer
    {
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLsizei stride;
        const void* pointer; // start offset
        bool enable = false;
    };

    struct VertexArray
    {
        GLuint VBO = 0;
        std::vector<VertexAttribPointer> attribPointers;
    };

    struct Buffer
    {
        void* data = nullptr;
    };

    struct GpuProgram
    {
        sgl::VertexShaderBase* vertexShader;
        sgl::FragmentShaderBase* fragShader;
        std::unordered_map<std::string, int> name2Id;
        std::unordered_map<int, std::vector<char>> id2data;

        GpuProgram(sgl::VertexShaderBase* vertexShader, sgl::FragmentShaderBase* fragShader) : vertexShader(vertexShader), fragShader(fragShader)
        {
            vertexShader->Init();
            fragShader->Init();

            for (auto it = vertexShader->GetName2Id().begin(); it != vertexShader->GetName2Id().end(); ++it)
            {
                ASSERT(name2Id.find(it->first) == name2Id.end());
                name2Id[it->first] = it->second;
            }
        }

        int GetUniformLocation(const std::string& name)
        {
            auto it = name2Id.find(name);
            if (it == name2Id.end())
                return 0;
            return it->second;
        }

        void SetUniformMatrix4fv(GLint location, GLsizei count, const GLfloat* value)
        {
            auto& data = id2data[location];
            int size = sizeof(glm::mat4) * count;
            data.resize(size);
            memcpy_s(&data[0], size, value, size);
        }

        const glm::mat4& GetUniformMatrix4fv(GLint location)
        {
            auto& data = id2data[location];
            return *(glm::mat4*)(&data[0]);
        }
    };

    struct TrianglePrimitive
    {

    };
}
