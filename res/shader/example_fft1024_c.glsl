#version 430

#define SIZE 1024

#define PI 3.14159265358979323844

uniform float roll;
uniform float test_frequency;
uniform int test_switch;

uniform float min_cut_filter;
uniform float max_cut_filter;

uniform float fft_display_scale;

layout (r32f, location = 0) uniform image1D destTex;
layout (local_size_x = SIZE) in;

shared vec2 values[SIZE][2];

void synchronize()
{
    memoryBarrierShared();
    barrier();
}

void fft_pass(int ns, int source, bool is_inverse)
{
    uint i = gl_LocalInvocationID.x;

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
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    uint i = gl_LocalInvocationID.x;

    if (test_switch == -1) {
        // deprecated
        // test_frequency hz test
        float val = 0.1*sin((pos.x * test_frequency * 3.f)/30.0 - roll);
        // 0.5 hz test
        val += 0.25 + 0.3*sin((pos.x * 0.5f * 3.f)/30.0 - roll);
        // 5 hz test
        val += 0.25 + 0.2*sin((pos.x * 5.f * 3.f)/30.0 - roll);
        imageStore(destTex, pos.x, vec4(val, 0.0f, 0.0f, 1.0f));
    } else if (test_switch == -2) {
        // deprecated
        // test_frequency hz test
        float val = 0.1*sin((pos.x * test_frequency * 3.f)/30.0 - roll);
        // 0.5 hz test
        val += 0.25 + 0.3*sin((pos.x * 0.5f * 3.f)/30.0 - roll);
        // 5 hz test
        val += 0.25 + 0.2*sin((pos.x * 5.f * 3.f)/30.0 - roll);

        values[i][0] = vec2(val, 0.);
        synchronize();

        int source = 0;

        for (int n = 2; n <= SIZE; n *= 2) {
            fft_pass(n, source, false);
            source ^= 1;
            synchronize();
        }

        float v = length(values[i][source]);

        imageStore(destTex, pos.x, vec4(v * fft_display_scale, 0.0f, 0.0f, 1.0f));
    } else if (test_switch == -3) {
        // deprecated
        // test_frequency hz test
        float val = 0.1*sin((pos.x * test_frequency * 3.f)/30.0 - roll);
        // 0.5 hz test
        val += 0.25 + 0.3*sin((pos.x * 0.5f * 3.f)/30.0 - roll);
        // 5 hz test
        val += 0.25 + 0.2*sin((pos.x * 5.f * 3.f)/30.0 - roll);

        values[i][0] = vec2(val, 0.);
        synchronize();

        int source = 0;

        for (int n = 2; n <= SIZE; n *= 2) {
            fft_pass(n, source, false);
            source ^= 1;
            synchronize();
        }

        // filter---------
        if (pos.x > min_cut_filter && pos.x < max_cut_filter ) {
            values[i][source].x = 0;
        }
        // end-------------

        for (int n = 2; n <= SIZE; n *= 2) {
            fft_pass(n, source, true);
            source ^= 1;
            synchronize();
        }

        float v = length(values[i][source]);

        imageStore(destTex, pos.x, vec4(v / SIZE, 0.0f, 0.0f, 1.0f));
    } else if (test_switch == 1) {
        vec4 v_ = imageLoad(destTex, pos.x);
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

        // filter---------
        if (pos.x >= min_cut_filter && pos.x <= max_cut_filter ) {
            v = 0;
        }

        imageStore(destTex, pos.x, vec4(v  * fft_display_scale , 0.0f, 0.0f, 1.0f));
    } else if (test_switch == 2) {
        vec4 v_ = imageLoad(destTex, pos.x);
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
        if (pos.x >= min_cut_filter && pos.x <= max_cut_filter ) {
            values[i][source] = vec2(0, 0);
        }

        float v = length(values[i][source]);

        imageStore(destTex, pos.x, vec4(v  * fft_display_scale, 0.0f, 0.0f, 1.0f));
    } else if (test_switch == 3) {
        vec4 v_ = imageLoad(destTex, pos.x);
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
        if (pos.x >= min_cut_filter && pos.x <= max_cut_filter ) {
            values[i][source] = vec2(0, 0);
        }
        // end-------------

        for (int n = 2; n <= SIZE; n *= 2) {
            fft_pass(n, source, true);
            source ^= 1;
            synchronize();
        }

        float v = length(values[i][source]);

        imageStore(destTex, pos.x, vec4(v / SIZE, 0.0f, 0.0f, 1.0f));
    }
}
