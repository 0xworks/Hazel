const std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoord;
layout(location = 3) in float a_texIndex;

uniform mat4 u_viewProjection;

out vec4 v_color;
out vec2 v_texCoord;
out float v_texIndex;


void main() {
   v_color = a_color;
   v_texCoord = a_texCoord;
   v_texIndex = a_texIndex;
   gl_Position = u_viewProjection * vec4(a_position, 1.0);
}
)";

const std::string fragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_texCoord;
in float v_texIndex;

uniform sampler2D u_textures[32];

void main() {
   color = texture(u_textures[int(v_texIndex)], v_texCoord) * v_color;
}
)";