#version 430
in vec2 pos;
out vec2 texCoord;

uniform float lineThickness;
uniform sampler1D srcTex;
uniform int display_switch;

uniform mat4 mvp_matrix;

void main() {
  if (display_switch == 6) {
    texCoord = pos*0.5f + 0.5f;

    vec4 v = texture(srcTex, texCoord.x);
    vec4 res = vec4(pos.x, pos.y * v.r, 0.0, 1.0);
    if (pos.y < 0) {
      res = vec4(pos.x, lineThickness - pos.y * v.r, 0.0, 1.0);
    }
    gl_Position = mvp_matrix * res;
    return;
  }
  texCoord = pos*0.5f + 0.5f;
  gl_Position = mvp_matrix * vec4(pos, 0.0, 1.0);
}
