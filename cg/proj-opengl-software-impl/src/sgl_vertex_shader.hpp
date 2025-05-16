#pragma once

#include <string>
#include "sglm.hpp"
#include "sgl_shader.hpp"

namespace sgl {
	class VertexShaderBase : public ShaderBase {
	protected:
		virtual void Init() = 0;
		virtual void MainFunc() = 0;

	protected:
		int RegisterUniformMat4(const std::string& name) {
			// todo
		}

		const glm::mat4& GetUniformMat4(int id) {

		}

		int RegisterInVec3(const std::string& name) {
			// todo
		}

		const glm::vec3& GetInVec3(int id) {

		}

		int RegisterInVec2(const std::string& name) {
			// todo
		}

		const glm::vec2& GetInVec2(int id) {

		}

		int RegisterOutVec2(const std::string& name) {
			// todo
		}

		glm::vec2& GetOutVec2(int id) {

		}

	protected:
		glm::vec4 gl_Position;
	};
}
