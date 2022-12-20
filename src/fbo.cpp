//
// Created by richard may clarkson on 10/12/2022.
//
#include "fbo.h"
#include "tex.h"

using namespace piqu;

namespace piqu {
  void init(fbo_t& in, bool depth, bool multisample) {
    tex::defaults(in.color, multisample);
    if (multisample) glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, in.width, in.height, false);
    else glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, in.width, in.height);
    die_if_gl("fbo_t::init>color>glTexStorage2D")
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, in.color, 0);
    die_if_gl("fbo_t::init>color>glFramebufferTexture2D")

    if (depth) {
      tex::defaults(in.depth);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, in.width, in.height, 0,
                   GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                             in.depth, 0);
    } else {
      in.depth = UINT32_MAX;
    }
  }

  fbo_t::fbo_t(i32 width, i32 height, bool depth, bool multisample) : multisample(multisample), width(width), height(height) {
    glGenFramebuffers(1, &this->handle);
    this->use();

    init(*this, depth, multisample);
  }

  void fbo_t::resize(i32 newWidth, i32 newHeight) {
    this->width = newWidth;
    this->height = newHeight;
    glDeleteTextures(1, &this->color);
    if (this->depth != UINT32_MAX) {
      glDeleteTextures(1, &this->depth);
    }
    init(*this, this->depth != UINT32_MAX, this->multisample);
  }
}