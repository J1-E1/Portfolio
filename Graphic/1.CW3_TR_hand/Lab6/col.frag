#version 330 core

in vec3 col;
in vec3 nor;
in vec3 FragPos;
in vec2 tex;

uniform sampler2D Texture;
uniform vec3 lightColour[2];
uniform vec3 lightDirection[2];
uniform vec3 lightPos[2];
uniform vec3 camPos;
uniform vec3 camPos_spot;

out vec4 fragCol;

float CalculateAttenuation(vec3 lightPos_factor)
{
	float att_c , att_l, att_q;
	att_c = 1.5;
	att_l = 0.05;
	att_q = 0.02;
	float d = length( lightPos_factor - FragPos );
	float attenuation  = 1 / ( att_c + ( att_l * d ) + ( att_q * d * d ));
	return attenuation;
}

float CalculateDirectionalIllumination( vec3 lightDirection_factor )
{
	float phong, ambient, diffuse, specular;
	ambient = 0.1;
	vec3 Nnor =  normalize(nor);
	vec3 Nto_light =  - normalize(lightDirection_factor );
	diffuse = dot(Nnor, Nto_light);

	vec3 Nfrom_light = normalize(lightDirection_factor);
	vec3 NrefLight = reflect(Nfrom_light , Nnor);
	vec3 camDirection = camPos -  FragPos;
	vec3 NcamDirection = normalize(camDirection);
	specular = pow( abs( dot(NcamDirection, NrefLight) ),128.0 );

	phong = ambient + diffuse + specular;
	return phong;

}

float CalculatePositionalIllumination(vec3 lightPos_factor)
{
	float phong, ambient, diffuse, specular;
	ambient = 0.1;
	
	vec3 Nnor =  normalize(nor);
	vec3 NToLight = normalize( lightPos_factor - FragPos );
	diffuse = dot(Nnor, NToLight);

	vec3 NFromLight = - NToLight;
	vec3 NrefLight = reflect(NFromLight , Nnor);
	vec3 camDirection = camPos -  FragPos;
	vec3 NcamDirection = normalize(camDirection);
	specular = pow( abs( dot(NcamDirection, NrefLight) ),256.0 );

	/* calculate attenuation */
	float attenuation = CalculateAttenuation(lightPos_factor);

	phong = (ambient + diffuse + specular) * attenuation;
	return phong;
	
}

 float CalculateSpotIllumination(vec3 lightDirection_factor, vec3 lightPos_factor )
{
	float phong, ambient, diffuse, specular;
	ambient = 0.1;
	
	vec3 Nnor =  normalize(nor);
	vec3 NToLight = normalize( lightPos_factor - FragPos );
	diffuse = dot(Nnor, NToLight);

	vec3 NFromLight = - NToLight;
	vec3 NrefLight = reflect(NFromLight , Nnor);
	vec3 camDirection = camPos_spot -  FragPos;
	vec3 NcamDirection = normalize(camDirection);
	specular = pow( abs( dot(NcamDirection, NrefLight) ),128.0 );

	/* calculate attenuation */
	float attenuation = CalculateAttenuation(lightPos_factor);

   /* For sport light */ 
	float cut_off_angle = 15.0f;
	float phi = cos( radians( cut_off_angle ) );
	vec3 NSpotDir = normalize( lightDirection_factor );
	float theta = dot( NFromLight, NSpotDir);

	if( theta > phi)
	{
		phong = (ambient + diffuse + specular) * attenuation;
	}else
	{
		phong = ambient * attenuation;
	}

	return phong;
}

void main()
{
	float phong_spot = CalculateSpotIllumination( lightDirection[0], lightPos[0] ) ; 
	float phong_position = CalculatePositionalIllumination( lightPos[1] );

	vec3 texCol = texture(Texture, tex).xyz;
	
	fragCol = vec4( (phong_spot + phong_position )* texCol  * lightColour[0], 1.f);
	

}
