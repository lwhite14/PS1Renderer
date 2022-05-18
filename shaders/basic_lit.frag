#version 460

in vec3 Position;
in vec3 Normal;

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

vec3 blinnPhong( vec3 position, vec3 normal ) 
{
	// Ambient
	vec3 ambient = Material.Ka * Light.La;

	// Diffuse
	vec3 s = normalize(vec3(Light.Position - vec4(position, 1.0f)));
	float sDotN = max( dot(s,normal), 0.0 );
	vec3 diffuse = Material.Kd * Light.Ld * sDotN;

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
	FragColor = vec4(blinnPhong(Position, normalize(Normal)), 1.0f);
}