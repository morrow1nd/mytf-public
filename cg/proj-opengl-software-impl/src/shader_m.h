#ifndef SHADER_H
#define SHADER_H

#/*include <glad/glad.h>
#include <glm/glm.hpp>*/
#include "sglad.h"
#include "sglm.hpp"
#include "sgl_shader.hpp"
#include "sgl.hpp"

#include <string>

class Shader
{
public:
    unsigned int ID;

    Shader(sgl::VertexShaderBase* vertexShader, sgl::FragmentShaderBase* fragShader) {
        ID = sglCreateProgram(vertexShader, fragShader);
    }

    //// constructor generates the shader on the fly
    //// ------------------------------------------------------------------------
    //Shader(const char* vertexPath, const char* fragmentPath)
    //{
    //    // 1. retrieve the vertex/fragment source code from filePath
    //    std::string vertexCode;
    //    std::string fragmentCode;
    //
    //    const char* vShaderCode = vertexCode.c_str();
    //    const char * fShaderCode = fragmentCode.c_str();
    //    // 2. compile shaders
    //    unsigned int vertex, fragment;
    //    // vertex shader
    //    vertex = glCreateShader(GL_VERTEX_SHADER);
    //    glShaderSource(vertex, 1, &vShaderCode, NULL);
    //    glCompileShader(vertex);
    //    checkCompileErrors(vertex, "VERTEX");
    //    // fragment Shader
    //    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    //    glShaderSource(fragment, 1, &fShaderCode, NULL);
    //    glCompileShader(fragment);
    //    checkCompileErrors(fragment, "FRAGMENT");
    //    // shader Program
    //    ID = glCreateProgram();
    //    glAttachShader(ID, vertex);
    //    glAttachShader(ID, fragment);
    //    glLinkProgram(ID);
    //    checkCompileErrors(ID, "PROGRAM");
    //    // delete the shaders as they're linked into our program now and no longer necessary
    //    glDeleteShader(vertex);
    //    glDeleteShader(fragment);
    //}

    // activate the shader
    // ------------------------------------------------------------------------
    void use() const
    { 
        glUseProgram(ID); 
    }

    // utility uniform functions
    //// ------------------------------------------------------------------------
    //void setBool(const std::string &name, bool value) const
    //{         
    //    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    //}
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    //// ------------------------------------------------------------------------
    //void setFloat(const std::string &name, float value) const
    //{ 
    //    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    //}
    //// ------------------------------------------------------------------------
    //void setVec2(const std::string &name, const glm::vec2 &value) const
    //{ 
    //    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    //}
    //void setVec2(const std::string &name, float x, float y) const
    //{ 
    //    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
    //}
    //// ------------------------------------------------------------------------
    //void setVec3(const std::string &name, const glm::vec3 &value) const
    //{ 
    //    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    //}
    //void setVec3(const std::string &name, float x, float y, float z) const
    //{ 
    //    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
    //}
    //// ------------------------------------------------------------------------
    //void setVec4(const std::string &name, const glm::vec4 &value) const
    //{ 
    //    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    //}
    //void setVec4(const std::string &name, float x, float y, float z, float w) const
    //{ 
    //    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
    //}
    //// ------------------------------------------------------------------------
    //void setMat2(const std::string &name, const glm::mat2 &mat) const
    //{
    //    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    //}
    //// ------------------------------------------------------------------------
    //void setMat3(const std::string &name, const glm::mat3 &mat) const
    //{
    //    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    //}
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        auto a = mat[0];
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    //// utility function for checking shader compilation/linking errors.
    //// ------------------------------------------------------------------------
    //void checkCompileErrors(GLuint shader, std::string type)
    //{
    //    GLint success;
    //    GLchar infoLog[1024];
    //    if (type != "PROGRAM")
    //    {
    //        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    //        if (!success)
    //        {
    //            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
    //            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    //        }
    //    }
    //    else
    //    {
    //        glGetProgramiv(shader, GL_LINK_STATUS, &success);
    //        if (!success)
    //        {
    //            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
    //            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    //        }
    //    }
    //}
};
#endif
