#version 460

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

layout( location = 0 ) out vec4 FragColor;

uniform struct LightInfo 
{
	vec4 Position;	
	vec3 La;
	vec3 Ld;
	vec3 Ls;
} Light;

uniform struct MaterialInfo 
{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
} Material;

uniform vec4 fogColour = vec4(0.4, 0.4, 0.4, 1.0);
uniform float fogMaxDist = 20.0;
uniform float fogMinDist = 0.25;

uniform sampler2D Tex1;

vec3 blinnPhong( vec3 position, vec3 normal ) 
{
	// Get Tex Colour
	vec3 texColour = texture(Tex1, TexCoord).rgb;

	// Ambient
	vec3 ambient = Material.Ka * Light.La * texColour;

	// Diffuse
	vec3 s = normalize(vec3(Light.Position - vec4(position, 1.0f)));
	float sDotN = max( dot(s,normal), 0.0 );
	vec3 diffuse = Material.Kd * Light.Ld * sDotN * texColour;

	// Specular
	vec3 spec = vec3(0.0);
	if( sDotN > 0.0 )
	{
		vec3 v = normalize(-position.xyz);
		vec3 h = normalize( v + s ); 
		spec = Material.Ks * pow( max( dot(h,normal), 0.0 ), Material.Shininess );
	}
	return ambient + diffuse + spec;
}

void main()
{
	// Calculate fog
	float dist = length(Position.xyz);
	float fogFactor = (fogMaxDist - dist) / (fogMaxDist - fogMinDist);
	fogFactor = clamp(fogFactor, 0.0, 1.0);
	       
	FragColor = mix(fogColour, vec4(blinnPhong(Position, normalize(Normal)), 1.0f), fogFactor);
}