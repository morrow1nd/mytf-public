#pragma once

#include "sglad.h"
#include "sgl_vertex_shader.hpp"
#include "sgl_fragment_shader.hpp"

void sglInit(int screenWidth, int screenHeight);
void sglRelease();
void sglPullPixels(uint32_t* pixels);
GLuint sglCreateProgram(sgl::VertexShaderBase* vertexShader, sgl::FragmentShaderBase* fragShader);
