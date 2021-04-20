#version 430

#define SIZE 512

#define PI 3.14159265358979323844

uniform float roll;

uniform float test_frequency;

uniform int test_switch;

layout (r32f, location = 0) uniform image1D destTex;
layout (local_size_x = SIZE) in;

shared vec2 values[SIZE][2];

void synchronize()
{
    memoryBarrierShared();
    barrier();
}

void fft_pass(int ns, int source)
{
    uint i = gl_LocalInvocationID.x;

    uint base = (i/ns) * (ns/2);
    uint offs = i % (ns/2);

    uint i0 = base + offs;
    uint i1 = i0 + SIZE/2;

    vec2 v0 = values[i0][source];
    vec2 v1 = values[i1][source];

    float a = -2. * PI * float(i)/ns;

    float t_re = cos(a);
    float t_im = sin(a);

    values[i][source ^ 1] = v0 + vec2(dot(vec2(t_re, -t_im), v1), dot(vec2(t_im, t_re), v1));
}

void main() {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    uint i = gl_LocalInvocationID.x;

    if (test_switch == -1) {
        float val = 0.25 + 0.2*sin((pos.x * test_frequency)/30.0 - roll);
        imageStore(destTex, pos.x, vec4(val, 0.0f, 0.0f, 1.0f));
    } else if (test_switch == 0) {
        vec4 v_ = imageLoad(destTex, pos.x);
        float val = v_.r;
        values[i][0] = vec2(val, 0.);
        synchronize();

        int source = 0;

        for (int n = 2; n <= SIZE; n *= 2) {
            fft_pass(n, source);
            source ^= 1;
            synchronize();
        }

        float v = length(values[i][source]);

        imageStore(destTex, pos.x, vec4(v / 100.f, 0.0f, 0.0f, 1.0f));
    } else if (test_switch == 1) {
        float val = 0.25 + 0.2*sin((pos.x * test_frequency)/30.0 - roll);
        values[i][0] = vec2(val, 0.);
        synchronize();

        int source = 0;

        for (int n = 2; n <= SIZE; n *= 2) {
            fft_pass(n, source);
            source ^= 1;
            synchronize();
        }

        float v = length(values[i][source]);

        imageStore(destTex, pos.x, vec4(v / 100.f, 0.0f, 0.0f, 1.0f));
    }
}
