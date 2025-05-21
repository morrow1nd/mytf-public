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
        std::unordered_map<std::string, int> name2Id;
        std::unordered_map<int, std::vector<char>> id2data;

        void AddNames(const std::unordered_map<std::string, int>& map)
        {
            for (auto it = map.cbegin(); it != map.cend(); ++it)
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
}
