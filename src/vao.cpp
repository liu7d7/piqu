//
// Created by richard may clarkson on 18/12/2022.
//

#include "vao.h"

namespace piqu {
  vao_t::vao_t() {
    glGenVertexArrays(1, &this->handle);
  }

  void vao_t::init(const vector<attrib>& attribs) {
    this->use();
    const i32 fSize{sizeof(float)};
    u64 offset{0};
    this->stride = 0;
    for (attrib i : attribs) this->stride += i;
    for (u32 i = 0; i < attribs.size(); i++) {
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(i, attribs[i], GL_FLOAT, false, this->stride * fSize, (void*) offset);
      offset += attribs[i] * fSize;
    }
  }
}