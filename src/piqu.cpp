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

namespace piqu
{
  GLFWwindow* window;
  int width, height;

  array<mat4, 7> stack;
  mat4* model;
  mat4 proj;
  mat4 look;
  int stackIdx{0};

  struct vertex_t
  {
    vec3 pos;
    vec4 color;
  };
  mesh_t<vertex_t>* mesh;
  fbo_t* fbo;

  void init()
  {
    i64 init = glfwInit();
    if (init != GLFW_TRUE)
    {
      die("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4);
    window = glfwCreateWindow(1152, 720, "test", nullptr, nullptr);
    width = 1152;
    height = 720;
    if (window == nullptr)
    {
      die("Failed to create Window!");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
      die("Failed to initialize GLAD!");
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height)
    {
      if (win != window) return;
      piqu::width = width;
      piqu::height = height;
      fbo->resize(width, height);
      glViewport(0, 0, width, height);
    });

    glClearColor(0, 0, 0, 0);

    for (int i = 0; i < 7; i++)
    {
      stack[i] = mat4(1.0f);
    }
    model = &stack[0];

    shader_t s("res/shader/tris.vert", "res/shader/tris.frag");
    mesh = new mesh_t<vertex_t>(draw_mode::triangle, s, vector<attrib>{attrib::float3, attrib::float4});
    fbo = new fbo_t(width, height, true, true);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);

    proj = perspective(radians(45.0f), (f32) width / (f32) height, 0.1f, 2000.0f);
    look = lookAt(vec3(500, 500, 500), vec3(0, 0, 0), vec3(0, 1, 0));

    stbi_set_flip_vertically_on_load(true);
  }

  void input()
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, true);
    }
  }

  void run()
  {
    f64 t = glfwGetTime();
    f64 dt;
    while (!glfwWindowShouldClose(window))
    {
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

  void tick()
  {

  }

  void draw(f64 dt)
  {
    fbo->use();
    fbo->clear();

    f32 time = (f32) glfwGetTime();
    f32 tp000 = (f32) time;
    f32 tp120 = (f32) (time + 120.0_rad);
    f32 tp240 = (f32) (time + 240.0_rad);

    const vec4 yellow = vec4(1.f, 0.91f, 0.3f, 1.f);
    const vec4 pink = vec4(1.f, 0.01f, 0.49f, 1.f);

    // tetrahedron
    vertex_t vertices[] = {
      /* top */ vertex_t{vec3(0, 0.75 * sin(tp000) * 2, 0), yellow},
      /* one */ vertex_t{vec3(0.5 * cos(tp120), 0, 0.5 * sin(tp120)), yellow},
      /* two */ vertex_t{vec3(0.5 * cos(tp240), 0, 0.5 * sin(tp240)), pink},
      /* three */ vertex_t{vec3(0.5 * cos(tp000), 0, 0.5 * sin(tp000)), pink},
    };

    vertices[0].pos *= 200;
    vertices[1].pos *= 200;
    vertices[2].pos *= 200;
    vertices[3].pos *= 200;

    mesh->begin();
    mesh->tri(
      mesh->put(vertices[0]),
      mesh->put(vertices[1]),
      mesh->put(vertices[2])
    );
    mesh->tri(
      mesh->put(vertices[0]),
      mesh->put(vertices[2]),
      mesh->put(vertices[3])
    );
    mesh->tri(
      mesh->put(vertices[0]),
      mesh->put(vertices[3]),
      mesh->put(vertices[1])
    );
//    mesh->tri(
//      mesh->put(vertices[1]),
//      mesh->put(vertices[3]),
//      mesh->put(vertices[2])
//    );
    mesh->draw();

    fbo_t::unuse();
    fbo->blit(0);
  }
}