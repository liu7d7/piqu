//
// Created by richard may clarkson on 19/12/2022.
//

#ifndef GLENGINE_GLSM_H
#define GLENGINE_GLSM_H

namespace gl
{
  extern bool depthEnabled;
  extern bool blendEnabled;
  extern bool cullEnabled;

  extern bool depthSaved;
  extern bool blendSaved;
  extern bool cullSaved;

  void save_state();

  void restore_state();

  void depth(bool on);

  void blend(bool on);

  void cull(bool on);
}

#endif //GLENGINE_GLSM_H
