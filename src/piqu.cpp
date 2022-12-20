//
// Created by richard may clarkson on 10/12/2022.
//
#include "piqu.h"
#include "stb_image.h"
#include "shader.h"
#include "vao.h"
#include "mesh.h"
#include "fbo.h"

using namespace piqu;

namespace piqu {
  GLFWwindow* window;

  array<mat4, 7> stack{};
  mat4* model;
  int stackIdx{0};

  int width, height;

  struct vertex_t {
    vec3 pos;
    vec4 color;
  };

  mesh_t<vertex_t>* mesh;
  fbo_t* fbo;

  void init() {
    i64 init = glfwInit();
    if (init != GLFW_TRUE) {
      die("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    window = glfwCreateWindow(1152, 720, "test", nullptr, nullptr);
    width = 1152;
    height = 720;
    if (window == nullptr) {
      die("Failed to create Window!");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      die("Failed to initialize GLAD!");
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height) {
      piqu::width = width;
      piqu::height = height;
      glViewport(0, 0, width, height);
    });

    glClearColor(0, 0, 0, 0);

    for (int i = 0; i < 7; i++) {
      stack[i] = mat4(1.0f);
    }
    model = &stack[0];

    shader_t s("res/shader/tris.vert", "res/shader/tris.frag");
    mesh = new mesh_t<vertex_t>(draw_mode::triangle, s, vector<attrib>{attrib::float3, attrib::float4});
    fbo = new fbo_t(width, height, false, true);

    stbi_set_flip_vertically_on_load(true);
  }

  void input() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
  }

  void run() {
    f64 t = glfwGetTime();
    f64 dt;
    while (!glfwWindowShouldClose(window)) {
      dt = glfwGetTime() - t;
      t = glfwGetTime();
      input();

      tick();
      draw(dt);

      glfwPollEvents();
      glfwSwapBuffers(window);
    }

    glfwTerminate();
  }

  void tick() {

  }

  void draw(f64 dt) {
    fbo->use();
    glClear(GL_COLOR_BUFFER_BIT);

    mesh->begin();
    mesh->tri(
      mesh->put(vertex_t{vec3(-sin(glfwGetTime()), -0.5f, 0.0f), vec4(1, 0, 0, 1)})->next(),
      mesh->put(vertex_t{vec3(0.5f, -sin(glfwGetTime()), 0.0f), vec4(0, 1, 0, 1)})->next(),
      mesh->put(vertex_t{vec3(sin(glfwGetTime()), 0.5f, 0.0f), vec4(0, 0, 1, 1)})->next()
    );
    mesh->draw();

    fbo_t::unuse();

    fbo->blit(0);
  }
}