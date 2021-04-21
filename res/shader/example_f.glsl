#version 430
uniform sampler1D srcTex;
uniform float lineThickness;
in vec2 texCoord;
out vec4 color;
uniform int display_switch;

void main() {
    if (display_switch == 0) {
        vec4 c = texture(srcTex, texCoord.s);
        float v1 = smoothstep(c.r - lineThickness/2.0, c.r, texCoord.y);
        float v2 = smoothstep(c.r + lineThickness/2.0, c.r, texCoord.y);
        color=vec4(min(v1, v2));
    } else if (display_switch == 1) {
        float v1 = texture(srcTex, texCoord.s).r;
        color = vec4(0.f, v1, 0.f, 1.f);
    }
}
