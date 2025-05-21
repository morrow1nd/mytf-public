#pragma once

#include "sgl.hpp"
#include "sgl_ds.hpp"
#include "sGPU.hpp"
#include "sgl_gpuprogram.hpp"

#include <vector>

class sGPU
{
public:
	bool glEnable_GL_DEPTH_TEST = false;
	sgl::ColorBuffer* colorBuffer = nullptr;
	sgl::DepthBuffer* depthBuffer = nullptr;
	std::vector<sgl::VertexArray*> sglVertexArrayPtrs;
	std::vector<sgl::Buffer*> sglBufferPtrs;
	std::vector<sgl::GpuProgram*> sglGpuPrograms;
	GLuint activeVAO = 0;
	GLuint activeGpuProgramId = 0;
	sgl::Color clearColor;
};
