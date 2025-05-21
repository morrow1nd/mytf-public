#include "sgl.hpp"
#include "sgl_ds.hpp"
#include "sGPU.hpp"
#include "sgl_gpuprogram.hpp"

#include <vector>

static sGPU gpu;

void glad_glEnable(GLenum cap)
{
    if (cap == GL_DEPTH_TEST)
    {
        gpu.glEnable_GL_DEPTH_TEST = true;
    }
    else
    {
        throw "no impl";
    }
}

void glad_glGenVertexArrays(GLsizei n, GLuint* arrays)
{
    for (int i = 0; i < n; ++i)
    {
        gpu.sglVertexArrayPtrs.push_back(new sgl::VertexArray());
        arrays[i] = gpu.sglVertexArrayPtrs.size() - 1;
    }
}

void glad_glGenBuffers(GLsizei n, GLuint* buffers)
{
    for (int i = 0; i < n; ++i)
    {
        gpu.sglBufferPtrs.push_back(new sgl::Buffer());
        buffers[i] = gpu.sglBufferPtrs.size() - 1;
    }
}

void glad_glBindVertexArray(GLuint VAO)
{
    gpu.activeVAO = VAO;
}

void glad_glBindBuffer(GLenum target, GLuint buffer)
{
    if (target == GL_ARRAY_BUFFER)
    {
        gpu.sglVertexArrayPtrs[gpu.activeVAO]->VBO = buffer;
    }
    else
    {
        throw "no impl";
    }
}

void glad_glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
    if (target == GL_ARRAY_BUFFER)
    {
        sgl::Buffer* VBO = gpu.sglBufferPtrs[gpu.sglVertexArrayPtrs[gpu.activeVAO]->VBO];
        VBO->data = malloc(size);
        memcpy_s(VBO->data, size, data, size); // todo: free VBO->data when no use
        // todo: argument usage
    }
    else
    {
        throw "no impl";
    }
}

void glad_glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
    sgl::VertexArray* VAO = gpu.sglVertexArrayPtrs[gpu.activeVAO];

    if (VAO->attribPointers.size() < (index + 1))
    {
        VAO->attribPointers.resize(index + 1);
    }
    sgl::VertexAttribPointer& p = VAO->attribPointers[index];
    p.size = size;
    p.type = type;
    p.normalized = normalized;
    p.stride = stride;
    p.pointer = pointer;
}

void glad_glEnableVertexAttribArray(GLuint index)
{
    sgl::VertexArray* VAO = gpu.sglVertexArrayPtrs[gpu.activeVAO];
    if (VAO->attribPointers.size() < (index + 1))
    {
        throw "error";
    }
    sgl::VertexAttribPointer& p = VAO->attribPointers[index];
    p.enable = true;
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClearColor.xhtml
// specify clear values for the color buffers
void glad_glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    gpu.clearColor.r = red;
    gpu.clearColor.g = green;
    gpu.clearColor.b = blue;
    gpu.clearColor.a = alpha;
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml
// render primitives from array data
void glad_glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
    sgl::VertexArray* VAO = gpu.sglVertexArrayPtrs[gpu.activeVAO];
    sgl::Buffer* VBO = gpu.sglBufferPtrs[VAO->VBO];

    sgl::GpuProgram* gpuProgram = gpu.sglGpuPrograms[gpu.activeGpuProgramId];

    if (mode == GL_TRIANGLES)
    {
        sgl::VertexShaderRuntimeEnv env;
        env.SetBuffer(VAO, VBO);
        env.SetGpuProgramRuntimeEnv(&gpuProgram->runtimeEnv);
        // 遍历每一个顶点
        for (int i = 0; i < count; ++i)
        {
            env.SetVertexIndex(i);
            gpuProgram->vertexShader->MainFunc(env);

        }
    }
    else
    {
        throw "no impl";
    }
}


void sglInit(int screenWidth, int screenHeight)
{
    // todo: move this code to class sGPU

    gpu.colorBuffer = new sgl::ColorBuffer(screenWidth, screenHeight);
    gpu.depthBuffer = new sgl::DepthBuffer(screenWidth, screenHeight);

    // keep index 0 for nullptr
    gpu.sglVertexArrayPtrs.push_back(nullptr);
    gpu.sglBufferPtrs.push_back(nullptr);
    gpu.sglGpuPrograms.push_back(nullptr);
}

void sglRelease()
{
    // todo: move this code to class sGPU

    delete gpu.colorBuffer;
    delete gpu.depthBuffer;
}

void sglPullPixels(uint32_t* pixels)
{

}

GLuint sglCreateProgram(sgl::VertexShaderBase* vertexShader, sgl::FragmentShaderBase* fragShader)
{
    gpu.sglGpuPrograms.push_back(new sgl::GpuProgram(vertexShader, fragShader));
    return gpu.sglGpuPrograms.size() - 1;
}

void glad_glUseProgram(GLuint program)
{
    gpu.activeGpuProgramId = program;
}

GLint glad_glGetUniformLocation(GLuint program, const GLchar* name)
{
    auto gpuProgram = gpu.sglGpuPrograms[program];
    return (GLint) gpuProgram->runtimeEnv.GetUniformLocation(name);
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml
// count: The count argument indicates the number of matrices to be passed. A count of 1 should be used if modifying the value of a single matrix, and a count greater than 1 can be used to modify an array of matrices.
// transpose: If transpose is GL_FALSE, each matrix is assumed to be supplied in column major order. If transpose is GL_TRUE, each matrix is assumed to be supplied in row major order. 
void glad_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    ASSERT(transpose == GL_FALSE);
    auto gpuProgram = gpu.sglGpuPrograms[gpu.activeGpuProgramId];
    gpuProgram->runtimeEnv.SetUniformMatrix4fv(location, count, value);
}
