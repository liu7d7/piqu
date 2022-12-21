//
// Created by richard may clarkson on 18/12/2022.
//

#include "vao.h"

namespace piqu
{
  vao_t::vao_t()
  {
    glGenVertexArrays(1, &handle);
  }

  void vao_t::init(const vector<attrib>& attribs)
  {
    use();
    const i32 fSize{sizeof(float)};
    u64 offset{0};
    stride = 0;
    for (attrib i : attribs) stride += i;
    for (u32 i = 0; i < attribs.size(); i++)
    {
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(i, attribs[i], GL_FLOAT, false, stride * fSize, (void*) offset);
      offset += attribs[i] * fSize;
    }
  }
}