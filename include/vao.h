//
// Created by richard may clarkson on 13/12/2022.
//

#ifndef GLENGINE_VAO_H
#define GLENGINE_VAO_H

#include "global.h"

namespace piqu
{
  enum attrib
  {
    float1 = 1, float2 = 2, float3 = 3, float4 = 4
  };

  struct vao_t
  {
    u32 handle;
    i32 stride;

    vao_t();

    void init(const vector<attrib>&);

    inline void use() const
    {
      glBindVertexArray(handle);
    }
  };

}

#endif //GLENGINE_VAO_H
