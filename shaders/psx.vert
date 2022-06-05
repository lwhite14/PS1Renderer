#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;

out vec3 Position;
out vec3 Normal;
noperspective out vec2 TexCoord;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

uniform vec2 TargetResolution = vec2(320, 240);

void main() 
{ 
	Normal = normalize( NormalMatrix * VertexNormal);
	Position = (ModelViewMatrix * vec4(VertexPosition,1.0)).xyz;
	TexCoord = VertexTexCoord;
	vec4 VertInClipSpace = MVP * vec4(VertexPosition,1.0); 

	vec2 grid = TargetResolution.xy * 0.5;
	vec4 snapped = VertInClipSpace;
	snapped.xyz = VertInClipSpace.xyz / VertInClipSpace.w;
	snapped.xy = floor(grid * snapped.xy) / grid;
	snapped.xyz *= VertInClipSpace.w;
	gl_Position = snapped;
}