#version 430

// pipeline-ból bejövõ per-fragment attribútumok
in vec3 vs_out_pos;
in vec3 vs_out_normal;
in vec2 vs_out_tex0;

// kimenõ érték - a fragment színe
out vec4 fs_out_col;

//
// uniform változók
//

// színtér tulajdonságok
uniform vec3 eye_pos = vec3(0, 15, 15);

// fénytulajdonságok
uniform vec3 light_pos = vec3( 5, 5, 5 );

uniform vec4 La = vec4(1, 1, 0.6f, 1);
uniform vec4 Ld = vec4(1, 1, 1, 1);
uniform vec4 Ls = vec4(1, 1, 1, 1);

// anyagtulajdonságok
uniform vec4 Ka = vec4(0.5f, 0.5f, 0.5f, 0);
uniform vec4 Kd = vec4(0.5f, 0.5f, 0.5f, 0);
uniform vec4 Ks = vec4(0.5f, 0.5f, 0.5f, 0);

uniform float specular_power = 32;
uniform sampler2D texImage;
uniform int meshID;
uniform int colValues[15][25];

void main()
{
	vec4 ambient = La * Ka;

	vec3 normal = normalize( vs_out_normal );
	if(!gl_FrontFacing) normal = -1 * normal;
	vec3 toLight = normalize(light_pos - vs_out_pos);
	float di = clamp( dot( toLight, normal), 0.0f, 1.0f );
	vec4 diffuse = vec4(Ld.rgb*Kd.rgb*di, Kd.a);

	vec4 specular = vec4(0);

	if ( di > 0 )
	{
		vec3 e = normalize( eye_pos - vs_out_pos );
		vec3 r = reflect( -toLight, normal );
		float si = pow( clamp( dot(e, r), 0.0f, 1.0f ), specular_power );
		specular = Ls*Ks*si;
	}

	//fs_out_col = vec4(((ambient + diffuse + specular ) * texture(texImage, vs_out_tex0.st)).xyz, 255.0 - meshID / 256.0);
	fs_out_col = vec4(((ambient + diffuse + specular ) * texture(texImage, vs_out_tex0.st)).xyz, 1.0);
}