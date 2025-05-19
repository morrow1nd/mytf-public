#pragma once

#include "sglad.h"
#include <vector>
#include "sgl_vertex_shader.hpp"
#include "sgl_fragment_shader.hpp"

namespace sgl {
	struct Color {
		union {
			struct { float r, g, b, a; };
		};

		// todo: default constructor
	};

	struct ColorBuffer {
		Color* data;

		ColorBuffer(int width, int height) {
			data = new Color[width * height];
		}

		~ColorBuffer() {
			delete[] data;
		}
	};

	struct DepthBuffer {
		float* data;

		DepthBuffer(int width, int height) {
			data = new float[width * height];
		}

		~DepthBuffer() {
			delete[] data;
		}
	};

	struct VertexAttribPointer {
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* pointer; // start offset
		bool enable = false;
	};

	struct VertexArray {
		GLuint VBO = 0;
		std::vector<VertexAttribPointer> attribPointers;
	};

	struct Buffer {
		void* data = nullptr;
	};

	struct GpuProgram {
		sgl::VertexShaderBase* vertexShader;
		sgl::FragmentShaderBase* fragShader;

		GpuProgram(sgl::VertexShaderBase* vertexShader, sgl::FragmentShaderBase* fragShader) : vertexShader(vertexShader), fragShader(fragShader) {}
	};

	struct TrianglePrimitive {

	};
}
