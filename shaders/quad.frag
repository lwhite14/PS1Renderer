#version 460

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
    FragColor = vec4(texture(Texture, TexCoord).rgb, 1.0);
} 