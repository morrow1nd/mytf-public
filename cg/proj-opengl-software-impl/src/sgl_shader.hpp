#pragma once

#include <string>
#include <unordered_map>
#include "sgl_base.hpp"
#include "sglm.hpp"
#include "sgl_ds.hpp"
#include "sgl_gpuprogram_runtime.hpp"

namespace sgl
{
    class ShaderRuntimeEnv
    {
    protected:
        sgl::GpuProgramRuntimeEnv* gpuProgramEnv = nullptr;

    public:
        void SetGpuProgramRuntimeEnv(sgl::GpuProgramRuntimeEnv* gpuProgramEnv)
        {
            this->gpuProgramEnv = gpuProgramEnv;
        }

    public:
        const glm::mat4& GetUniformMat4(int id)
        {
            return this->gpuProgramEnv->GetUniformMatrix4fv(id);
        }

        glm::vec4 texture(int id, const glm::vec2& texCoord)
        {
            // todo
            return glm::vec4();
        }


        const glm::vec2& GetInVec2(int id)
        {
            // todo
            return glm::vec2();
        }

        glm::vec4& GetOutVec4(int id)
        {
            // todo
            return glm::vec4();
        }
    };

    class ShaderBase
    {
    public:
        const std::unordered_map<std::string, int>& GetName2Id() { return name2Id; }
        const std::unordered_map<std::string, int>& GetUniformName2Id() { return uniformName2Id; }

    protected:
        std::unordered_map<std::string, int> name2Id;
        std::unordered_map<std::string, int> uniformName2Id;

        int RegisterName(const std::string& name)
        {
            auto it = name2Id.find(name);
            if (it != name2Id.end())
                return it->second;

            static int sId = 0;
            return name2Id[name] = ++sId;
        }

        int RegisterUniformMat4(const std::string& name)
        {
            int id = RegisterName(name);
            uniformName2Id[name] = id;
            return id;
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


        int RegisterOutVec4(const std::string& name)
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
