cmake_minimum_required(VERSION 3.23)
project(glEngine)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glm/glm)

find_package(OpenGL REQUIRED)

include_directories(libs/glfw/include/GLFW)
include_directories(libs/glad)
include_directories(libs/glm/glm)
include_directories(include)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(glEngine main.cpp include/piqu.h include/global.h src/piqu.cpp libs/glad/glad.h libs/glad/glad.c include/fbo.h src/fbo.cpp include/tex.h src/tex.cpp include/stb_image.h include/shader.h src/shader.cpp include/buf.h include/vao.h src/vao.cpp include/mesh.h include/draw_mode.h include/glsm.h src/glsm.cpp)
target_link_libraries(glEngine glfw)
