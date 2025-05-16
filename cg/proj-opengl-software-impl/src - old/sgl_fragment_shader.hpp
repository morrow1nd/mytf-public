#pragma once

#include <string>
#include "sglm.hpp"
#include "sgl_shader.hpp"

namespace sgl {
	class FragmentShaderBase : public ShaderBase {
	protected:
		virtual void Init() = 0;
		virtual void MainFunc() = 0;

	protected:
		int RegisterInVec2(const std::string& name) {
			// todo
			return 0;
		}

		const glm::vec2& GetInVec2(int id) {
			// todo
			return glm::vec2();
		}

		int RegisterUniformSampler2D(const std::string& name) {
			// todo
			return 0;
		}

		glm::vec4 texture(int id, const glm::vec2& texCoord) {
			// todo
			return glm::vec4();
		}

		glm::vec4 output;
	};
}