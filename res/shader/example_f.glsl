#version 430
uniform sampler1D srcTex;
in vec2 texCoord;
out vec4 color;
void main() {
    vec4 c = texture(srcTex, texCoord.s);
    color=vec4(c);
}
