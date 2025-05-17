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
			return 0;
		}

		const glm::mat4& GetUniformMat4(int id) {
			// todo
			return glm::mat4(0);
		}

		int RegisterInVec3(const std::string& name) {
			// todo
			return 0;
		}

		const glm::vec3& GetInVec3(int id) {
			// todo
			return glm::vec3();
		}

		int RegisterInVec2(const std::string& name) {
			// todo
			return 0;
		}

		const glm::vec2& GetInVec2(int id) {
			// todo
			return glm::vec2();
		}

		int RegisterOutVec2(const std::string& name) {
			// todo
			return 0;
		}

		glm::vec2& GetOutVec2(int id) {
			// todo
			return glm::vec2();
		}

	protected:
		glm::vec4 gl_Position;
	};
}
