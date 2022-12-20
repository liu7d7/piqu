//
// Created by richard may clarkson on 10/12/2022.
//

#ifndef GLENGINE_FBO_H
#define GLENGINE_FBO_H

#include "global.h"

namespace piqu {
  struct fbo_t {
    u32 handle;
    u32 color;
    u32 depth;
    i32 width;
    i32 height;
    bool multisample;

    fbo_t(i32, i32, bool depth = false, bool multisample = false);

    void resize(i32, i32);

    inline void use() const {
      glBindFramebuffer(GL_FRAMEBUFFER, handle);
    }

    static inline void unuse() {
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    inline void blit(const fbo_t& in) const {
      glBindFramebuffer(GL_READ_FRAMEBUFFER, this->handle);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, in.handle);
      glBlitFramebuffer(0, 0, this->width, this->height, 0, 0, in.width, in.height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    }

    inline void blit(u32 in) const {
      glBindFramebuffer(GL_READ_FRAMEBUFFER, this->handle);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, in);
      glBlitFramebuffer(0, 0, this->width, this->height, 0, 0, this->width, this->height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    }
  };
}

#endif //GLENGINE_FBO_H
