//
// Created by richard may clarkson on 10/12/2022.
//

#ifndef GLENGINE_TEX_H
#define GLENGINE_TEX_H

#include "global.h"

namespace piqu {
  struct tex_t {
    u32 handle;
    i32 width;
    i32 height;

    explicit tex_t(const string& src);

    explicit tex_t(u8* src, i32 width, i32 height);

    inline void use() const {
      glBindTexture(GL_TEXTURE_2D, handle);
    }
  };

  namespace tex {
    void defaults(u32& handle, bool multisample = false);
  }
}

#endif //GLENGINE_TEX_H
