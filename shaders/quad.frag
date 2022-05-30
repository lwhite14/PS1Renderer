#version 460 core

in vec2 UV;

out vec3 FragColour;

uniform sampler2D RenderedTexture;
uniform float Time;

void main()
{
	FragColour = texture(RenderedTexture, UV + 0.005 * vec2(sin(Time + 1024.0 * UV.x), cos(Time + 768.0 * UV.y))).xyz;
}