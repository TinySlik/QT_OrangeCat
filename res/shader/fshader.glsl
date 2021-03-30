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


float hash( float n ) { return fract(sin(n)*753.5453123); }

// Slight modification of iq's noise function.
float noise( in vec2 x )
{
    vec2 p = floor(x);
    vec2 f = fract(x);
    f = f*f*(3.0-2.0*f);

    float n = p.x + p.y*157.0;
    return mix(
                    mix( hash(n+  0.0), hash(n+  1.0),f.x),
                    mix( hash(n+157.0), hash(n+158.0),f.x),
            f.y);
}


float fbm(vec2 p, vec3 a)
{
     float v = 0.0;
     v += noise(p*a.x)*.50;
     v += noise(p*a.y)*.50;
     v += noise(p*a.z)*.125;
     return v;
}

vec3 drawLines( vec2 uv, vec3 fbmOffset,  vec3 color2 )
{
    float timeVal = time * 0.1;
    vec3 finalColor = vec3( 0.0 );

    for( int i=0; i < 1; ++i )
    {
        float indexAsFloat = float(i);
        float amp = 8.0 + (indexAsFloat*7.0);
        float period = 2.0 + (indexAsFloat+8.0);
        float thickness = mix( 0.7, 1.0, noise(uv*10.0) );
        float t = abs( 1.0 / (sin(uv.x + fbm( uv + timeVal * period, fbmOffset )) * amp) * thickness );

        finalColor +=  t * color2 * 0.6;
    }

    return finalColor;
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main( void )
{

    vec2 pos = vert.xy / 1.0; // resolution-independent position relative to lower-left screen corner
      //vec2 pos = (gl_FragCoord.xy - 0.5*R) / R.y; // resolution-independent position relative to screen center
      //vec2 pos = (gl_FragCoord.xy - M*R) / R.y; // resolution-independent position relative to mouse position
      //vec2 pos = gl_FragCoord.xy / R.y - 0.2*vec2(T, sin(T)); // resolution-independent position relative to moving center

      float freq = 16.0; vec2 tile = floor(pos * freq); // convert position into tile coordinates

      vec3 rgb = vec3(mod(tile.x + tile.y, 2.0)); // black-and-white chessboard
      //float steps = 5.0; vec3 rgb = vec3(mod(tile.x + tile.y, steps) / (steps - 1.0)); // multi-gray chessboard
      //vec3 rgb = vec3(mod(tile.x, 2.0), mod(tile.y, 3.0), mod(tile.x + tile.y, 2.0)); // multi-color chessboard
      //vec3 rgb = vec3(min(min(tile.x, tile.y), min(freq-tile.x, freq-tile.y)) * 2.0 / freq); // concentric squares

   gl_FragColor = vec4(rgb.r,rgb.g,rgb.b, 1.0); // set fragment color

}
