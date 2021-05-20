#version 430

#define SIZE 4096

#define PI 3.14159265358979323844
uniform float roll;
uniform float test_frequency;
uniform int test_switch;

uniform float min_cut_filter;
uniform float max_cut_filter;

uniform float fft_display_scale;

layout (r32f, location = 0) uniform image1D destTex;
layout (local_size_x = 512, 8) in;

shared vec2 values[SIZE][2];

void synchronize()
{
    memoryBarrierShared();
    barrier();
}

void fft_pass(int ns, int source, bool is_inverse)
{
    uint i = gl_LocalInvocationID.x + gl_LocalInvocationID.y * 512;

    uint base = (i/ns) * (ns/2);
    uint offs = i % (ns/2);

    uint i0 = base + offs;
    uint i1 = i0 + SIZE/2;

    vec2 v0 = values[i0][source];
    vec2 v1 = values[i1][source];

    float a = -2. * PI * float(i) * float(int(!is_inverse) * 2 - 1)/ns;

    float t_re = cos(a);
    float t_im = sin(a);

    values[i][source ^ 1] = v0 + vec2(dot(vec2(t_re, -t_im), v1), dot(vec2(t_im, t_re), v1));
}

void main() {
    int pos = gl_GlobalInvocationID.x + gl_GlobalInvocationID.y * 512;
    uint i = gl_LocalInvocationID.x + gl_LocalInvocationID.y * 512;

    if (test_switch == 1) {
        vec4 v_ = imageLoad(destTex, pos);
        float val = v_.r;
        values[i][0] = vec2(val, 0.);
        synchronize();

        int source = 0;

        for (int n = 2; n <= SIZE; n *= 2) {
            fft_pass(n, source, false);
            source ^= 1;
            synchronize();
        }

        float v = length(values[i][source]);

        imageStore(destTex, pos, vec4(v  * fft_display_scale , 0.0f, 0.0f, 1.0f));
    } else if (test_switch == 2) {
        vec4 v_ = imageLoad(destTex, pos);
        float val = v_.r;
        values[i][0] = vec2(val, 0.);
        synchronize();

        int source = 0;

        for (int n = 2; n <= SIZE; n *= 2) {
            fft_pass(n, source, false);
            source ^= 1;
            synchronize();
        }

        // filter---------
        if (pos >= min_cut_filter && pos <= max_cut_filter ) {
            values[i][source] = vec2(0, 0);
        }

        float v = length(values[i][source]);

        imageStore(destTex, pos, vec4(v  * fft_display_scale, 0.0f, 0.0f, 1.0f));
    } else if (test_switch == 3 || test_switch == 4 || test_switch == 5) {
        vec4 v_ = imageLoad(destTex, pos);
        float val = v_.r;
        values[i][0] = vec2(val, 0.);
        synchronize();

        int source = 0;

        for (int n = 2; n <= SIZE; n *= 2) {
            fft_pass(n, source, false);
            source ^= 1;
            synchronize();
        }

        // filter---------
        if (pos >= min_cut_filter && pos <= max_cut_filter ) {
            values[i][source] = vec2(0, 0);
        }
        // end-------------

        for (int n = 2; n <= SIZE; n *= 2) {
            fft_pass(n, source, true);
            source ^= 1;
            synchronize();
        }

        float v = length(values[i][source]);

        imageStore(destTex, pos, vec4(v / SIZE, 0.0f, 0.0f, 1.0f));
    }
}
