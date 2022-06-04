#version 460

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ScreenTexture;

void main()
{
    FragColor = vec4(texture(ScreenTexture, TexCoord).rgb, 1.0);
} 