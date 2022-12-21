//
// Created by richard may clarkson on 19/12/2022.
//

#ifndef GLENGINE_MESH_H
#define GLENGINE_MESH_H

#include "buf.h"
#include "vao.h"
#include "shader.h"
#include "draw_mode.h"
#include "glsm.h"

namespace piqu
{
  template<typename T>
  struct mesh_t
  {
    draw_mode_t drawMode;
    buf_t<T> vbo;
    buf_t<u32> ibo;
    vao_t vao;
    shader_t shader;
    u32 vertex;
    u32 index;
    bool building;

    mesh_t(const draw_mode_t& mode, shader_t& shader, const vector<attrib>& attribs) :
      vbo(buf_t<T>(GL_ARRAY_BUFFER, 1200)), ibo(buf_t<u32>(GL_ELEMENT_ARRAY_BUFFER, 1200)), drawMode(mode),
      shader(shader), building(false), vao(vao_t()), index(0), vertex(0)
    {
      vbo.use();
      ibo.use();
      vao.init(attribs);
    }

    u32 next()
    {
      return vertex++;
    }

    u32 put(const T& p0)
    {
      vbo.put(p0);
      return vertex++;
    }

    void single(u32 p0)
    {
      ibo.put(p0);
      index++;
    }

    void line(u32 p0, u32 p1)
    {
      ibo.put(p0);
      ibo.put(p1);
      index += 2;
    }

    void tri(u32 p0, u32 p1, u32 p2)
    {
      ibo.put(p0);
      ibo.put(p1);
      ibo.put(p2);
      index += 3;
    }

    void quad(u32 p0, u32 p1, u32 p2, u32 p3)
    {
      ibo.put(p0);
      ibo.put(p1);
      ibo.put(p2);
      ibo.put(p2);
      ibo.put(p3);
      ibo.put(p0);
      index += 6;
    }

    void begin()
    {
      if (building)
      {
        die("Already building!");
      }
      building = true;

      vbo.clear();
      ibo.clear();

      vertex = index = 0;
    }

    void end()
    {
      if (!building)
      {
        die("Not building!");
      }
      building = false;

      if (index > 0)
      {
        vbo.upload();
        ibo.upload();
      }
    }

    void draw()
    {
      if (building) end();
      if (index == 0) return;

      gl::save_state();
      gl::blend(true);
      gl::depth(true);
      shader.use();
      shader.set_defaults();
      ibo.use();
      vbo.use();
      vao.use();
      glDrawElements(drawMode.cap, index, GL_UNSIGNED_INT, nullptr);
      gl::restore_state();
      die_if_gl("mesh_t::draw>end")
    }
  };
}

#endif //GLENGINE_MESH_H
