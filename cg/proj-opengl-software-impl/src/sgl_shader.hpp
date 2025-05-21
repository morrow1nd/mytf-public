#pragma once

#include <string>
#include <unordered_map>
#include "sgl_base.hpp"
#include "sglm.hpp"
#include "sgl_ds.hpp"

namespace sgl
{
    class ShaderRuntimeEnv
    {
        sgl::GpuProgram* gpuProgram = nullptr;

    public:
        void SetGpuProgram(sgl::GpuProgram* gpuProgram)
        {
            this->gpuProgram = gpuProgram;
        }

    public:
        const glm::mat4& GetUniformMat4(int id)
        {
            return this->gpuProgram->GetUniformMatrix4fv(id);
        }

        glm::vec2& GetOutVec2(int id)
        {
            // todo
            return glm::vec2();
        }


        const glm::vec2& GetInVec2(int id)
        {
            // todo
            return glm::vec2();
        }

        glm::vec4 texture(int id, const glm::vec2& texCoord)
        {
            // todo
            return glm::vec4();
        }
    };

    class ShaderBase
    {
    public:
        std::unordered_map<std::string, int>& GetName2Id() { return name2Id; }

    protected:
        std::unordered_map<std::string, int> name2Id;
        int uniformDataSize = 0;

        int RegisterName(const std::string& name)
        {
            static int sId = 0;
            return name2Id[name] = ++sId;
        }

        int RegisterUniformMat4(const std::string& name)
        {
            uniformDataSize += sizeof(glm::vec4);
            return RegisterName(name);
        }

        int RegisterInVec3(const std::string& name)
        {
            // todo
            return RegisterName(name);
        }

        int RegisterInVec2(const std::string& name)
        {
            // todo
            return RegisterName(name);
        }

        int RegisterOutVec2(const std::string& name)
        {
            // todo
            return RegisterName(name);
        }


        int RegisterInVec2(const std::string& name)
        {
            // todo
            return RegisterName(name);
        }

        int RegisterUniformSampler2D(const std::string& name)
        {
            // todo
            return RegisterName(name);
        }
    };
}
