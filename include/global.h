//
// Created by richard may clarkson on 10/12/2022.
//

#ifndef GLENGINE_GLOBAL_H
#define GLENGINE_GLOBAL_H

#include "glm.hpp"
#include "glad.h"
#include "glfw3.h"
#include "iostream"
#include "unordered_map"
#include "vector"
#include "streambuf"
#include "sstream"
#include "fstream"

inline std::string gl_to_string(GLenum en) {
  switch (en) {
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
    case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_ARRAY_BUFFER: return "GL_ARRAY_BUFFER";
    case GL_ELEMENT_ARRAY_BUFFER: return "GL_ELEMENT_ARRAY_BUFFER";
    case GL_STATIC_DRAW: return "GL_STATIC_DRAW";
    case GL_DYNAMIC_DRAW: return "GL_DYNAMIC_DRAW";
    case GL_STREAM_DRAW: return "GL_STREAM_DRAW";
    case GL_FLOAT: return "GL_FLOAT";
    case GL_UNSIGNED_INT: return "GL_UNSIGNED_INT";
    case GL_UNSIGNED_BYTE: return "GL_UNSIGNED_BYTE";
    case GL_TRIANGLES: return "GL_TRIANGLES";
    case GL_TRIANGLE_STRIP: return "GL_TRIANGLE_STRIP";
    case GL_TRIANGLE_FAN: return "GL_TRIANGLE_FAN";
    case GL_POINTS: return "GL_POINTS";
    case GL_LINES: return "GL_LINES";
    case GL_LINE_STRIP: return "GL_LINE_STRIP";
    case GL_LINE_LOOP: return "GL_LINE_LOOP";
    case GL_COMPILE_STATUS: return "GL_COMPILE_STATUS";
    case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
    case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
    case GL_LINK_STATUS: return "GL_LINK_STATUS";
    case GL_TEXTURE_2D: return "GL_TEXTURE_2D";
    default: return "UNKNOWN";
  }
}

#define die(loc) glfwTerminate(); cout << (loc) << '\n'; exit(1)

#define die_if_gl(loc) \
  { \
    GLenum error = GL_NO_ERROR; \
    error = glGetError(); \
    if (GL_NO_ERROR != error) { \
      std::cout << "die_if_gl: " << gl_to_string(error) << " at " << (loc) << '!' << '\n'; \
      glfwTerminate(); \
      exit(1); \
    } \
  }

typedef int i32;
typedef long long i64;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned char u8;
typedef float f32;
typedef double f64;

using namespace std;
using namespace glm;

#endif //GLENGINE_GLOBAL_H
