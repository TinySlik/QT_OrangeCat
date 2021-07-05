#version 430

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler1D srcTex;
uniform float lineThickness;
uniform vec4 front_color;
uniform vec4 background_color;
in vec2 texCoord;
out vec4 color;
uniform int display_switch;

// glslsandbox uniforms
uniform float time;
vec2 resolution = vec2(1.f, 1.f);

void main() {
  color = front_color;
}
