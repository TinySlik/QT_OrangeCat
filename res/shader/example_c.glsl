#version 430
uniform float roll;
uniform image1D destTex;
layout (local_size_x = 256, local_size_y = 1) in;
void main() {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    float val=0.5+0.2*sin((pos.x+pos.y)/30.0+roll);
    imageStore(destTex, pos.x, vec4(val, 0.5f, 0.5f, 1.0f));
}
