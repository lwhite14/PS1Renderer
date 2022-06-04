#version 460

in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;

uniform sampler2D Tex1;

void main()
{
	FragColor = texture(Tex1, TexCoord);
}