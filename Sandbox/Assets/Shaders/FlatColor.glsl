#version 330 core

#ifdef VERTEX_SHADER

layout(location = 0) in vec3 a_position;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

void main() {
   gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
}
#endif


#ifdef FRAGMENT_SHADER

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main() {
   color = u_color;
}
#endif
