//
// Created by richard may clarkson on 11/12/2022.
//

#ifndef GLENGINE_SHADER_H
#define GLENGINE_SHADER_H

#include "global.h"
#include "gtc/type_ptr.hpp"
#include "piqu.h"

namespace piqu
{
  struct shader_t
  {
    u32 handle;
    unordered_map<string, i32> uniforms;

    shader_t(const string&, const string&);

    shader_t(const string&, const string&, const string&);

    inline void set_float(const string& name, float val)
    {
      glUniform1f(uniforms[name], val);
      die_if_gl("shader_t::set_float")
    }

    inline void set_mat4(const string& name, const mat4& val)
    {
      glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, &val[0][0]);
      die_if_gl("shader_t::set_mat4")
    }

    inline void set_vec2(const string& name, const vec2& val)
    {
      glUniform2f(uniforms[name], val[0], val[1]);
      die_if_gl("shader_t::set_vec2")
    }

    inline void set_vec3(const string& name, const vec3& val)
    {
      glUniform3f(uniforms[name], val[0], val[1], val[2]);
      die_if_gl("shader_t::set_vec3")
    }

    inline void set_vec4(const string& name, const vec4& val)
    {
      glUniform4f(uniforms[name], val[0], val[1], val[2], val[3]);
      die_if_gl("shader_t::set_vec4")
    }

    inline void set_defaults()
    {
      set_mat4("u_proj", piqu::proj);
      set_mat4("u_look", piqu::look);
    }

    inline void use() const
    {
      glUseProgram(handle);
    }
  };
}

#endif //GLENGINE_SHADER_H
