//
// Created by richard may clarkson on 10/12/2022.
//
#include "fbo.h"
#include "tex.h"

using namespace piqu;

namespace piqu
{
  void init(fbo_t& in, bool depth, bool multisample)
  {
    tex::defaults(in.color, multisample);
    if (multisample) glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, in.width, in.height, false);
    else
      glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, in.width, in.height);
    die_if_gl("fbo_t::init>color>glTexStorage2D")
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, in.color, 0);
    die_if_gl("fbo_t::init>color>glFramebufferTexture2D")

    if (depth)
    {
      if (multisample)
      {
        tex::defaults(in.depth, multisample);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_DEPTH_COMPONENT24, in.width, in.height, false);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, in.depth, 0);
        die_if_gl("fbo_t::init>depth>glTexImage2DMultisample")
      }
      else
      {
        tex::defaults(in.depth);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, in.width, in.height, 0,
                     GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                               in.depth, 0);
        die_if_gl("fbo_t::init>depth>!multisample>glFramebufferTexture2D")
      }
    }
    else
    {
      in.depth = UINT32_MAX;
    }

    u32 code = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (code != GL_FRAMEBUFFER_COMPLETE)
    {
      die("fbo_t::init>glCheckFramebufferStatus(" + gl_to_string(code) + ")");
    }
  }

  fbo_t::fbo_t(i32 width, i32 height, bool depth, bool multisample) : multisample(multisample), width(width),
                                                                      height(height)
  {
    glGenFramebuffers(1, &handle);
    use();

    init(*this, depth, multisample);
  }

  void fbo_t::resize(i32 newWidth, i32 newHeight)
  {
    width = newWidth;
    height = newHeight;
    glDeleteTextures(1, &color);
    if (depth != UINT32_MAX)
    {
      glDeleteTextures(1, &depth);
    }
    use();
    init(*this, depth != UINT32_MAX, multisample);
  }
}