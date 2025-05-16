#pragma once

#include "sglad.h"
#include <vector>

namespace sgl {
	struct Color {
		union {
			struct { float r, g, b, a; };
		};
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
}
