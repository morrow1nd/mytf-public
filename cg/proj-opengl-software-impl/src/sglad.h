#pragma once

#include <cstdint>

#  define GLAPI
#define APIENTRY
//#define APIENTRYP APIENTRY *
#define APIENTRYP APIENTRY

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLclampx;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef char GLchar;
typedef uint64_t GLsizeiptr;

#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_COLOR_BUFFER_BIT 0x00004000

#define GL_FALSE 0
#define GL_TRUE 1

#define GL_TRIANGLES 0x0004

#define GL_BYTE 0x1400
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406
#define GL_DOUBLE 0x140A

#define GL_DEPTH_TEST 0x0B71
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_TEXTURE_2D 0x0DE1

#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803

#define GL_REPEAT 0x2901

#define GL_LINEAR 0x2601

#define GL_ALPHA 0x1906
#define GL_RGB 0x1907
#define GL_RGBA 0x1908

#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF
#define GL_ACTIVE_TEXTURE 0x84E0


//typedef void (APIENTRYP PFNGLENABLEPROC)(GLenum cap);
//GLAPI PFNGLENABLEPROC glad_glEnable;
void glad_glEnable(GLenum cap);
#define glEnable glad_glEnable

typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
GLAPI PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;
#define glGenVertexArrays glad_glGenVertexArrays

typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
GLAPI PFNGLGENBUFFERSPROC glad_glGenBuffers;
#define glGenBuffers glad_glGenBuffers

typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint array);
GLAPI PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
#define glBindVertexArray glad_glBindVertexArray

typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
GLAPI PFNGLBINDBUFFERPROC glad_glBindBuffer;
#define glBindBuffer glad_glBindBuffer

typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
GLAPI PFNGLBUFFERDATAPROC glad_glBufferData;
#define glBufferData glad_glBufferData

typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
GLAPI PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
#define glVertexAttribPointer glad_glVertexAttribPointer

typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
#define glEnableVertexAttribArray glad_glEnableVertexAttribArray

typedef void (APIENTRYP PFNGLGENTEXTURESPROC)(GLsizei n, GLuint* textures);
GLAPI PFNGLGENTEXTURESPROC glad_glGenTextures;
#define glGenTextures glad_glGenTextures

typedef void (APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
GLAPI PFNGLBINDTEXTUREPROC glad_glBindTexture;
#define glBindTexture glad_glBindTexture

typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
GLAPI PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
#define glTexParameteri glad_glTexParameteri

typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
GLAPI PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
#define glTexImage2D glad_glTexImage2D

typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC)(GLenum target);
GLAPI PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap;
#define glGenerateMipmap glad_glGenerateMipmap

void glad_glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
#define glClearColor glad_glClearColor

typedef void (APIENTRYP PFNGLCLEARPROC)(GLbitfield mask);
GLAPI PFNGLCLEARPROC glad_glClear;
#define glClear glad_glClear

typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum texture);
GLAPI PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
#define glActiveTexture glad_glActiveTexture

typedef void (APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
GLAPI PFNGLDRAWARRAYSPROC glad_glDrawArrays;
#define glDrawArrays glad_glDrawArrays

typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint* arrays);
GLAPI PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
#define glDeleteVertexArrays glad_glDeleteVertexArrays

typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint* buffers);
GLAPI PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
#define glDeleteBuffers glad_glDeleteBuffers

typedef void (APIENTRYP PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
GLAPI PFNGLVIEWPORTPROC glad_glViewport;
#define glViewport glad_glViewport


// shader

//#define GL_FRAGMENT_SHADER 0x8B30
//#define GL_VERTEX_SHADER 0x8B31
//
//#define GL_DELETE_STATUS 0x8B80
//#define GL_COMPILE_STATUS 0x8B81
//#define GL_LINK_STATUS 0x8B82
//
//typedef GLuint(APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
//GLAPI PFNGLCREATESHADERPROC glad_glCreateShader;
//#define glCreateShader glad_glCreateShader
//
//typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
//GLAPI PFNGLSHADERSOURCEPROC glad_glShaderSource;
//#define glShaderSource glad_glShaderSource
//
//typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint shader);
//GLAPI PFNGLCOMPILESHADERPROC glad_glCompileShader;
//#define glCompileShader glad_glCompileShader
//
//typedef GLuint(APIENTRYP PFNGLCREATEPROGRAMPROC)();
//GLAPI PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
//#define glCreateProgram glad_glCreateProgram
//
//typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
//GLAPI PFNGLATTACHSHADERPROC glad_glAttachShader;
//#define glAttachShader glad_glAttachShader
//
//typedef void (APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint program);
//GLAPI PFNGLLINKPROGRAMPROC glad_glLinkProgram;
//#define glLinkProgram glad_glLinkProgram
//
//typedef void (APIENTRYP PFNGLDELETESHADERPROC)(GLuint shader);
//GLAPI PFNGLDELETESHADERPROC glad_glDeleteShader;
//#define glDeleteShader glad_glDeleteShader

void glad_glUseProgram(GLuint program);
#define glUseProgram glad_glUseProgram

GLint glad_glGetUniformLocation(GLuint program, const GLchar* name);
#define glGetUniformLocation glad_glGetUniformLocation

typedef void (APIENTRYP PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
GLAPI PFNGLUNIFORM1IPROC glad_glUniform1i;
#define glUniform1i glad_glUniform1i

void glad_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
#define glUniformMatrix4fv glad_glUniformMatrix4fv

//typedef void (APIENTRYP PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint* params);
//GLAPI PFNGLGETSHADERIVPROC glad_glGetShaderiv;
//#define glGetShaderiv glad_glGetShaderiv
//typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
//GLAPI PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;
//#define glGetShaderInfoLog glad_glGetShaderInfoLog
//typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
//GLAPI PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
//#define glGetProgramiv glad_glGetProgramiv
//typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
//GLAPI PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
//#define glGetProgramInfoLog glad_glGetProgramInfoLog
