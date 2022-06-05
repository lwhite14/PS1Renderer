#version 460

in vec3 Position;
in vec3 Normal;
noperspective in vec2 TexCoord;
noperspective in vec3 Colour;

layout( location = 0 ) out vec4 FragColor;

uniform vec4 fogColour = vec4(0.4, 0.4, 0.4, 1.0);
uniform float fogMaxDist = 20.0;
uniform float fogMinDist = 0.25;

uniform sampler2D Texture;

void main()
{
	// Calculate fog
	float dist = length(Position.xyz);
	float fogFactor = (fogMaxDist - dist) / (fogMaxDist - fogMinDist);
	fogFactor = clamp(fogFactor, 0.0, 1.0);
	       
	vec4 textureFragment = texture(Texture, TexCoord);
	vec4 shadedFragment = textureFragment * vec4(Colour, 1.0);
	vec4 fogFragment = mix(fogColour, shadedFragment, fogFactor);
	FragColor = fogFragment;
}