//
// Created by richard may clarkson on 19/12/2022.
//

#ifndef GLENGINE_DRAW_MODE_H
#define GLENGINE_DRAW_MODE_H

#include "global.h"

namespace piqu
{
  struct draw_mode_t
  {
    i32 size;
    u32 cap;
  };

  namespace draw_mode
  {
    static const draw_mode_t line{2, GL_LINES};
    static const draw_mode_t triangle{3, GL_TRIANGLES};
    static const draw_mode_t triangle_strip{2, GL_TRIANGLE_STRIP};
  }
}
#endif //GLENGINE_DRAW_MODE_H
