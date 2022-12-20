//
// Created by richard may clarkson on 11/12/2022.
//
#include "tex.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

namespace piqu::tex {
  void defaults(u32& handle, bool multisample) {
    glGenTextures(1, &handle);
    glBindTexture(multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, handle);
    if (multisample) return;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    die_if_gl("tex::defaults")
  }
}

piqu::tex_t::tex_t(u8* src, i32 width, i32 height) {
  tex::defaults(this->handle);
  this->width = width;
  this->height = height;
  if (src) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, src);
  } else {
    die("failed to load texture from " + to_string(((u64) src)));
  }
}

piqu::tex_t::tex_t(const string& src) {
  tex::defaults(this->handle);
  unsigned char* data = stbi_load(src.c_str(), &this->width, &this->height, nullptr, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  } else {
    die("failed to load texture from " + src);
  }
}
