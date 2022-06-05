#version 460

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Texture;
uniform float Time;
uniform vec2 Resolution;

vec2 CRTCurveUV( vec2 uv )
{
    uv = uv * 2.0 - 1.0;
    vec2 offset = abs( uv.yx ) / vec2( 6.0, 4.0 );
    uv = uv + uv * offset * offset;
    uv = uv * 0.5 + 0.5;
    return uv;
}

vec3 DrawVignette( vec3 color, vec2 uv )
{    
    float vignette = uv.x * uv.y * ( 1.0 - uv.x ) * ( 1.0 - uv.y );
    vignette = clamp( pow( 16.0 * vignette, 0.3 ), 0.0, 1.0 );
    color *= vignette;
    return color;
}

vec3 DrawScanline( vec3 color, vec2 uv )
{
    float scanline 	= clamp( 0.95 + 0.05 * cos( 3.14 * ( uv.y + 0.008 * Time ) * 240.0 * 1.0 ), 0.0, 1.0 );
    float grille 	= 0.85 + 0.15 * clamp( 1.5 * cos( 3.14 * uv.x * 640.0 * 1.0 ), 0.0, 1.0 );    
    color *= scanline * grille * 1.2;
    return color;
}


void main()
{
    vec3 color = texture(Texture, TexCoord).rgb;

    vec2 uv = gl_FragCoord.xy / Resolution.xy;
    vec2 crtUV = CRTCurveUV( uv );
    if ( crtUV.x < 0.0 || crtUV.x > 1.0 || crtUV.y < 0.0 || crtUV.y > 1.0 )
    {
        color = vec3( 0.0, 0.0, 0.0 );
    }
    vec3 colorVignette = DrawVignette( color, crtUV );
    vec3 colorScanline = DrawScanline( colorVignette, uv );
    
	FragColor.xyz 	= colorScanline;
    FragColor.w		= 1.0;
} 