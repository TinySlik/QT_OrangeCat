#version 430
uniform sampler1D srcTex;
uniform float lineThickness;
in vec2 texCoord;
out vec4 color;

void main() {
    vec4 c = texture(srcTex, texCoord.s);
    float v1 = smoothstep(c.r - lineThickness/2.0, c.r, texCoord.y);
    float v2 = smoothstep(c.r + lineThickness/2.0, c.r, texCoord.y);
    color=vec4(min(v1, v2));
}
