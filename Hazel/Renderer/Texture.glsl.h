const std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_textureCoord;
layout(location = 3) in float a_textureIndex;
layout(location = 4) in float a_tilingFactor;


uniform mat4 u_viewProjection;

out vec4 v_color;
out vec2 v_textureCoord;
out float v_textureIndex;
out float v_tilingFactor;


void main() {
   v_color = a_color;
   v_textureCoord = a_textureCoord;
   v_textureIndex = a_textureIndex;
   v_tilingFactor = a_tilingFactor;
   gl_Position = u_viewProjection * vec4(a_position, 1.0);
}
)";

const std::string fragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_textureCoord;
in float v_textureIndex;
in float v_tilingFactor;

uniform sampler2D u_textures[32];

void main() {
   color = texture(u_textures[int(v_textureIndex)], v_textureCoord * v_tilingFactor) * v_color;
}
)";