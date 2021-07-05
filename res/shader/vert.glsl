#version 430
in vec2 pos;
out vec2 texCoord;

uniform sampler1D srcTex;

uniform mat4 mvp_matrix;

void main() {
     texCoord = pos*0.5f + 0.5f;
     gl_Position = mvp_matrix * vec4(pos, 0.0, 1.0);
}
