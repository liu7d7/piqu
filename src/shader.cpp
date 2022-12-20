//
// Created by richard may clarkson on 11/12/2022.
//
#include "shader.h"
#include "gtc/type_ptr.hpp"

namespace piqu {
  u32 shader_source(const string& src, u32 type) {
    ifstream file(src);
    stringstream stream;
    stream << file.rdbuf();
    file.close();
    u32 out = glCreateShader(type);
    string source = stream.str();
    auto buf = source.c_str();
    glShaderSource(out, 1, &buf, nullptr);
    glCompileShader(out);
    i32 t;
    glGetShaderiv(out, GL_COMPILE_STATUS, &t);
    if (t == GL_TRUE) return out;
    char log[512];
    glGetShaderInfoLog(out, 512, nullptr, log);
    string l = log;
    die("compile " + gl_to_string(type) + " " + l);
  }

  void do_uniforms(shader_t& in) {
    i32 numUniforms;
    glGetProgramiv(in.handle, GL_ACTIVE_UNIFORMS, &numUniforms);
    in.uniforms = unordered_map<string, i32>();

    for (u32 i = 0; i < numUniforms; i++) {
      char* buf = new char[256];
      i32 len;
      glGetActiveUniform(in.handle, i, 256, &len, nullptr, nullptr, buf);
      i32 loc = glGetUniformLocation(in.handle, buf);
      string str = buf;
      in.uniforms[str] = loc;
      delete[] buf;
    }
  }

  void link_program(shader_t& in) {
    glLinkProgram(in.handle);
    i32 t;
    glGetProgramiv(in.handle, GL_LINK_STATUS, &t);
    if (t == GL_TRUE) return;
    char* buf = new char[256];
    glGetProgramInfoLog(in.handle, 256, nullptr, buf);
    string str = buf;
    delete[] buf;
    die("link " + gl_to_string(t) + " " + str);
  }

  shader_t::shader_t(const string& vsrc, const string& fsrc) {
    u32 vsh = shader_source(vsrc, GL_VERTEX_SHADER);
    u32 fsh = shader_source(fsrc, GL_FRAGMENT_SHADER);

    this->handle = glCreateProgram();
    glAttachShader(this->handle, vsh);
    glAttachShader(this->handle, fsh);

    link_program(*this);

    glDetachShader(this->handle, vsh);
    glDeleteShader(vsh);
    glDetachShader(this->handle, fsh);
    glDeleteShader(fsh);

    do_uniforms(*this);
  }

  shader_t::shader_t(const string& vsrc, const string& fsrc, const string& gsrc) {
    u32 vsh = shader_source(vsrc, GL_VERTEX_SHADER);
    u32 fsh = shader_source(fsrc, GL_FRAGMENT_SHADER);
    u32 gsh = shader_source(fsrc, GL_GEOMETRY_SHADER);

    this->handle = glCreateProgram();
    glAttachShader(this->handle, vsh);
    glAttachShader(this->handle, fsh);
    glAttachShader(this->handle, gsh);

    link_program(*this);

    glDetachShader(this->handle, vsh);
    glDeleteShader(vsh);
    glDetachShader(this->handle, fsh);
    glDeleteShader(fsh);
    glDetachShader(this->handle, gsh);
    glDeleteShader(gsh);

    do_uniforms(*this);
  }
}