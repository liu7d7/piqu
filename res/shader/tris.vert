#version 330 core
in vec3 pos;
in vec4 color;

out vec4 v_color;

void main() {
  gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
  v_color = color;
}