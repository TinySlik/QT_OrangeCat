#version 430

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler1D srcTex;
uniform float lineThickness;
in vec2 texCoord;
out vec4 color;
uniform int display_switch;

// glslsandbox uniforms
uniform float time;
vec2 resolution = vec2(1.f, 1.f);

void main() {
    if (display_switch == 0) {
        vec4 c = texture(srcTex, texCoord.s);
        float v1 = smoothstep(c.r - lineThickness/2.0, c.r, texCoord.y);
        float v2 = smoothstep(c.r + lineThickness/2.0, c.r, texCoord.y);
        color=vec4(min(v1, v2));
    } else if (display_switch == 1) {
        float v1 = texture(srcTex, texCoord.s).r;
        color = vec4(0.f, v1, 0.f, 1.f);
    } else if (display_switch == 2) {
        vec4 c = texture(srcTex, texCoord.s);
        float v1 = smoothstep(c.r - lineThickness/2.0, c.r, texCoord.y);
        color=vec4(0.0, 1.0 - v1, 0.0, 1.0);
    } else if (display_switch == 3) {
        vec4 c = texture(srcTex, texCoord.s);
        float v1 = pow(1.0 - abs(texCoord.t - c.r), 50.0);
        color=vec4(v1);
    } else if (display_switch == 4) {

        vec2 uv = (texCoord.xy * 2. - resolution) / resolution.x;
        vec3 color_;
        float y = uv.y + time;
        for (int i = 0; i < 3; i++) {
            float d = uv.x - sin(y * float(3+i)/3.) * .7;
            color_[i] = .01 / (d * d);
        }
        color = vec4(color_, 1.0);

    } else if (display_switch == 5) {
        vec2 p = (texCoord.xy * 2.0 - resolution) / min(resolution, resolution);
        vec3 color_ = vec3(0.0, 0.3, 0.5);

        float f = 0.0;
        float PI = 3.141592;
        for(float i = 0.0; i < 20.0; i++){

          float s = sin(time*1.1 + i * PI / 10.0) * 0.28 ;
          float c = cos(time*1.1 + i * PI / 10.0) * 0.28;

          f += 0.001 / pow( pow(abs(p.x + c),2.) + pow(abs(p.y + s),2.),.534+0.5*sin(-time*3.321+i/3.14159265+s*c*0.1));
        }
        color = vec4(vec3(  f*color_), 1.0);
    }
}
