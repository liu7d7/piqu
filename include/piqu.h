//
// Created by richard may clarkson on 10/12/2022.
//

#ifndef GLENGINE_PIQU_H
#define GLENGINE_PIQU_H

#include "global.h"
#include "fbo.h"

namespace piqu {
  extern GLFWwindow* window;

  // stack
  extern array<mat4, 7> stack;
  extern mat4* model;
  extern int stackIdx;
  extern fbo_t* fbo;

  inline void push() {
    stackIdx++;
    stack[stackIdx] = mat4(stack[stackIdx - 1]);
    model = &stack[stackIdx];
  }

  inline void pop() {
    stackIdx--;
    model = &stack[stackIdx];
  }

  inline void translate(const vec3& vec) {
    stack[stackIdx] = (*model) * translate(identity<mat4>(), vec);
    model = &stack[stackIdx];
  }

  extern int width, height;

  void init();

  void run();

  void tick();

  void draw(f64 dt);
}

#endif //GLENGINE_PIQU_H
