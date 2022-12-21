//
// Created by richard may clarkson on 19/12/2022.
//
#include "glsm.h"
#include "glad.h"

namespace gl
{
  bool depthEnabled{false};
  bool blendEnabled{false};
  bool cullEnabled{false};

  bool depthSaved{false};
  bool blendSaved{false};
  bool cullSaved{false};

  void save_state()
  {
    depthSaved = depthEnabled;
    blendSaved = blendEnabled;
    cullSaved = cullEnabled;
  }

  void restore_state()
  {
    depth(depthSaved);
    blend(blendSaved);
    cull(cullSaved);
  }

  void depth(bool on)
  {
    if (depthEnabled == on) return;
    depthEnabled = on;
    if (on)
    {
      glEnable(GL_DEPTH_TEST);
    }
    else
    {
      glDisable(GL_DEPTH_TEST);
    }
  }

  void blend(bool on)
  {
    if (blendEnabled == on) return;
    blendEnabled = on;
    if (on)
    {
      glEnable(GL_BLEND);
    }
    else
    {
      glDisable(GL_BLEND);
    }
  }

  void cull(bool on)
  {
    if (cullEnabled == on) return;
    cullEnabled = on;
    if (on)
    {
      glEnable(GL_CULL_FACE);
    }
    else
    {
      glDisable(GL_CULL_FACE);
    }
  }
}