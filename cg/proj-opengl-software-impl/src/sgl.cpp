#include "sgl.hpp"
#include "sgl_ds.hpp"

#include <vector>

static bool glEnable_GL_DEPTH_TEST = false;
static sgl::ColorBuffer* colorBuffer = nullptr;
static sgl::DepthBuffer* depthBuffer = nullptr;
static std::vector<sgl::VertexArray*> sglVertexArrayPtrs;
static std::vector<sgl::Buffer*> sglBufferPtrs;
static GLuint activeVAO = 0;


void glad_glEnable(GLenum cap) {
	if (cap == GL_DEPTH_TEST) {
		glEnable_GL_DEPTH_TEST = true;
	}
	else {
		throw "no impl";
	}
}

void glad_glGenVertexArrays(GLsizei n, GLuint* arrays) {
	for (int i = 0; i < n; ++i) {
		sglVertexArrayPtrs.push_back(new sgl::VertexArray());
		arrays[i] = sglVertexArrayPtrs.size() - 1;
	}
}

void glad_glGenBuffers(GLsizei n, GLuint* buffers) {
	for (int i = 0; i < n; ++i) {
		sglBufferPtrs.push_back(new sgl::Buffer());
		buffers[i] = sglBufferPtrs.size() - 1;
	}
}

void glad_glBindVertexArray(GLuint VAO) {
	activeVAO = VAO;
}

void glad_glBindBuffer(GLenum target, GLuint buffer) {
	if (target == GL_ARRAY_BUFFER) {
		sglVertexArrayPtrs[activeVAO]->VBO = buffer;
	}
	else {
		throw "no impl";
	}
}

void glad_glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
	if (target == GL_ARRAY_BUFFER) {
		sgl::Buffer* VBO = sglBufferPtrs[sglVertexArrayPtrs[activeVAO]->VBO];
		VBO->data = malloc(size);
		memcpy_s(VBO->data, size, data, size); // todo: free VBO->data when no use
		// todo: argument usage
	}
	else {
		throw "no impl";
	}
}

void glad_glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
	sgl::VertexArray* VAO = sglVertexArrayPtrs[activeVAO];

	if (VAO->attribPointers.size() < (index + 1)) {
		VAO->attribPointers.resize(index + 1);
	}
	sgl::VertexAttribPointer& p = VAO->attribPointers[index];
	p.size = size;
	p.type = type;
	p.normalized = normalized;
	p.stride = stride;
	p.pointer = pointer;
}

void glad_glEnableVertexAttribArray(GLuint index) {
	sgl::VertexArray* VAO = sglVertexArrayPtrs[activeVAO];
	if (VAO->attribPointers.size() < (index + 1)) {
		throw "error";
	}
	sgl::VertexAttribPointer& p = VAO->attribPointers[index];
	p.enable = true;
}

// one drawcall
void glad_glDrawArrays(GLenum mode, GLint first, GLsizei count) {
	if (mode != GL_TRIANGLES) {
		throw "no impl";
	}


}


void sglInit(int screenWidth, int screenHeight) {
	colorBuffer = new sgl::ColorBuffer(screenWidth, screenHeight);
	depthBuffer = new sgl::DepthBuffer(screenWidth, screenHeight);

	// keep index 0 for nullptr
	sglVertexArrayPtrs.push_back(nullptr);
	sglBufferPtrs.push_back(nullptr);
}

void sglRelease() {
	delete colorBuffer;
	delete depthBuffer;
}

void sglPullPixels(uint32_t* pixels) {

}

GLuint sglCreateProgram(sgl::VertexShaderBase* vertexShader, sgl::FragmentShaderBase* fragShader) {

}
