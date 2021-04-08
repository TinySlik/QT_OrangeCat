varying highp vec3 vert;
varying highp vec3 vertNormal;
uniform highp vec3 lightPos;
uniform float time;
//void main() {
//  highp vec3 L = normalize(lightPos - vert);
//  highp float NL = max(dot(normalize(vertNormal), L), 0.0);
//  highp vec3 color = vec3(0.39, 1.0, 0.0);
//  highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);
//  gl_FragColor = vec4(0.5, 0.5, 0.5, 1.0);
//}

// 随泥浆脉冲信号去噪算法验证demo (论文同步页数)

const vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
const vec4 color1 = vec4(1.0, 0.7, 0.7, 1.0);
const vec4 color2 = vec4(0.2, 0.2, 0.9, 1.0);
const vec4 color3 = vec4(0.9, 0.0, 0.2, 1.0);
const vec4 color4 = vec4(0.2, 1.0, 0.2, 1.0);
const vec4 color5 = vec4(0.6, 0.5, 0.2, 1.0);

float rand(float n){return fract(sin(n) * 43758.5453123);}

// 随机噪声
float noise0(float p){
        float fl = floor(p);
  float fc = fract(p);
        return mix(rand(fl), rand(fl + 1.0), fc);
}

// 活塞运动噪声(5hz)
float noise1(float p){
  float fl = floor(p);
  float fc = fract(p);
  return mix(rand(fl), rand(fl + 1.0), fc);
}
#if 0
void main( void )
{
        vec2 position = vert.xy * 20.0;

        float x = position.x;
        float y = position.y;

        float d1 = 0.12, d2 = 0.00;
        gl_FragColor = white;
        if ((y > -d1)&&((y < d1)))   gl_FragColor = black;
        if ((x > -d1)&&((x < d1)))   gl_FragColor = black;

        if (((fract(x) < d2 || (fract(x) > 1.0 - d2)) && abs(y) < 0.25))   gl_FragColor = black;
        if (((fract(y) < d2 || (fract(y) > 1.0 - d2)) && abs(x) < 0.25))   gl_FragColor = black;

        // 基础波形使用三角函数曲线.
        // 三钢绑活塞运动噪声(5hz)
        // functions
        float fx1 = sin((x+time) * 5.0) ;
        // 相邻三钢绑干扰噪声(0.5hz)
        fx1 = fx1 + 3.0 * cos((x+time) * 0.5);

//        float fx2 = cos(x+time * 2.0);
//        float fx2 = 2.0*smoothstep(-2.,2.,x)-1.;
//        float fx3 = x/sqrt(1.0+pow(x,2.0));
//        float fx4 = x/sqrt(1.0+pow(x,4.0));
//        float fx5 = 2.0*sin(4.*x)/x;

        if ((y < fx1+d1)&&((y > fx1-d2))) gl_FragColor = color1;
//        if ((y < fx2+d1)&&((y > fx2-d2))) gl_FragColor = color2;
//        if ((y < fx3+d1)&&((y > fx3-d2))) gl_FragColor = color3;
//        if ((y < fx4+d1)&&((y > fx4-d2))) gl_FragColor = color4;
//        if ((y < fx5+d1)&&((y > fx5-d2))) gl_FragColor = color5;
}
#endif

void main( void )
{
    vec2 me = vec2(vert.x + (mod(time, 500.f))/ 5.0, vert.y) * 20.0;
    float y = 0.0;
    y += mix(noise0(me.x*4.0 * 5.0)*0.25,noise0(me.x*4.0+1.0)*5.f,.15);
    y += mix(noise0(me.x*2.0 * 5.0)*0.25,noise0(me.x*2.0+1.0)*1.f,.15);
    y += mix(noise0(me.x*4.0 * 5.0)*0.25,noise0(me.x*1.0+1.0)*1.f,.15);
    y += mix(noise0(me.x*4.0 * 5.0)*0.25,noise0(me.x*5.0+1.0)*1.f,.15);
    if ( me.y < y + .05 && me.y  > y - .04)
            gl_FragColor = vec4(1.0);
    else
            gl_FragColor = vec4(0.0);
}
