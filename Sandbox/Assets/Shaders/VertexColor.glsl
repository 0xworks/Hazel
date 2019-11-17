#version 330 core

#ifdef VERTEX_SHADER

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

out vec4 v_color;

void main() {
   v_color = a_color;
   gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
}
#endif


#ifdef FRAGMENT_SHADER

layout(location = 0) out vec4 color;

in vec4 v_color;

void main() {
   color = vec4(v_color);
}
#endif
