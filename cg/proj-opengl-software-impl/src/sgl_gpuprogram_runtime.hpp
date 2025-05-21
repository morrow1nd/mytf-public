#pragma once

#include "sgl_base.hpp"
#include "sglad.h"
#include "sglm.hpp"

#include <string>
#include <unordered_map>

namespace sgl
{
    struct GpuProgramRuntimeEnv
    {
        // todo: remove these code
        //std::unordered_map<int, std::vector<char>> vertexShaderOutDataId2data;

        //void RegisterVertexShaderOutDataTypes(const std::unordered_map<int, LayoutDataType>& id2OutDataType)
        //{
        //    for (auto it = id2OutDataType.cbegin(), end = id2OutDataType.cend(); it != end; ++it)
        //    {
        //        const LayoutDataType& type = it->second;
        //        auto& buffer = vertexShaderOutDataId2data[it->first];
        //        buffer.resize((type.arraySize == 0 ? 1 : type.arraySize) * type.sizeofDataType * type.size);
        //        memset(&buffer[0], 0, buffer.size());
        //    }
        //}

        //void* GetVertexShaderOutDataPtr(int id)
        //{
        //    auto it = vertexShaderOutDataId2data.find(id);
        //    ASSERT(it != vertexShaderOutDataId2data.end());
        //    return &((it->second)[0]);
        //}


        std::unordered_map<std::string, int> uniformName2Id;
        std::unordered_map<int, std::vector<char>> uniformId2data;

        void AddUniformNames(const std::unordered_map<std::string, int>& map)
        {
            for (auto it = map.cbegin(); it != map.cend(); ++it)
            {
                ASSERT(uniformName2Id.find(it->first) == uniformName2Id.end());
                uniformName2Id[it->first] = it->second;
            }
        }

        int GetUniformLocation(const std::string& name)
        {
            auto it = uniformName2Id.find(name);
            if (it == uniformName2Id.end())
                return 0;
            return it->second;
        }

        void SetUniformMatrix4fv(GLint location, GLsizei count, const GLfloat* value)
        {
            auto& data = uniformId2data[location];
            int size = sizeof(glm::mat4) * count;
            data.resize(size);
            memcpy_s(&data[0], size, value, size);
        }

        const glm::mat4& GetUniformMatrix4fv(GLint location)
        {
            auto& data = uniformId2data[location];
            return *(glm::mat4*)(&data[0]);
        }
    };
}
