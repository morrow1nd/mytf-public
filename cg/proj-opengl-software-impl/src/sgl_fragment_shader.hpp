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
		}

		const glm::vec2& GetInVec2(int id) {

		}

		int RegisterUniformSampler2D(const std::string& name) {

		}

		glm::vec4 texture(int id, const glm::vec2& texCoord) {

		}

		glm::vec4 output;
	};
}