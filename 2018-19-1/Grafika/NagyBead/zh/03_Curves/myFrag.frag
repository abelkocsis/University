#version 130

// pipeline-b�l bej�v� per-fragment attrib�tumok
in vec3 vs_out_pos;
in vec3 vs_out_normal;
in vec2 vs_out_tex0;

// kimen� �rt�k - a fragment sz�ne
out vec4 fs_out_col;

//
// uniform v�ltoz�k
//

uniform float x;
uniform float y;

// sz�nt�r tulajdons�gok
uniform vec3 eye_pos;
//vec3 eye_pos = vec3(x, 15, y);

// f�nytulajdons�gok
//uniform 
uniform vec3 light_pos;
uniform vec3 light_pos2;
uniform int light2_active;


uniform vec3 La = vec3(0.25, 0.86, 0.92);
uniform vec3 Ld2 = vec3(1, 0.84, 0f);
uniform vec3 Ld = vec3(0, 1, 0);
uniform vec3 Ls = vec3(1, 0, 0);
uniform vec3 Ls2 = vec3(1, 0.84, 0);

// anyagtulajdons�gok
uniform vec3 Ka = vec3(0.5, 0.5, 0.5);
uniform vec3 Kd = vec3(0.75, 0.45, 0.125);
uniform vec3 Ks = vec3(1, 1, 1);


uniform float specular_power = 50;
uniform float specular_power2 = 75;
uniform sampler2D texImage;
uniform int ball_active;




void main()
{
	//
	// ambiens sz�n sz�m�t�sa
	//
	vec3 ambient = La * Ka;

	//
	// diff�z sz�n sz�m�t�sa
	//

	/* seg�ts�g:
		- normaliz�l�s: http://www.opengl.org/sdk/docs/manglsl/xhtml/normalize.xml
	    - skal�ris szorzat: http://www.opengl.org/sdk/docs/manglsl/xhtml/dot.xml
	    - clamp: http://www.opengl.org/sdk/docs/manglsl/xhtml/clamp.xml
	*/
	vec3 normal = normalize( vs_out_normal );
	vec3 toLight = normalize(light_pos - vs_out_pos);
	float di = clamp( dot( toLight, normal), 0.0f, 1.0f );
	vec3 diffuse = di*Ld*Kd;

	float di2 = 0;
	vec3 diffuse2 = vec3(0,0,0);
	
	vec3 toLight2 = normalize(light_pos2 - vs_out_pos);
	di2 = clamp( dot( toLight2, normal), 0.0f, 1.0f );
	diffuse2 = di2*Ld2*Kd;

		
	

	

	//
	// f�nyfoltk�pz� sz�n
	//

	/* seg�ts�g:
		- reflect: http://www.opengl.org/sdk/docs/manglsl/xhtml/reflect.xml
		- power: http://www.opengl.org/sdk/docs/manglsl/xhtml/pow.xml
	*/
	vec3 specular = vec3(0);
	vec3 specular2 = vec3(0);

	if ( di > 0 )
	{
		vec3 e = normalize( eye_pos - vs_out_pos );
		vec3 r = reflect( -toLight, normal );
		float si = pow( clamp( dot(e, r), 0.0f, 1.0f ), specular_power );
		specular = Ls*Ks*si;
	}
	if ( di2 > 0 )
	{
		vec3 e2 = normalize( eye_pos - vs_out_pos );
		vec3 r2 = reflect( -toLight2, normal );
		float si2 = pow( clamp( dot(e2, r2), 0.0f, 1.0f ), specular_power2 );
		specular2 = Ls2*Ks*si2;
	}

	vec3 feny = ambient + diffuse + specular;
	if (light2_active == 1){
		feny += diffuse2 + specular2;
	}

	fs_out_col = vec4(feny, 1) * texture(texImage, vs_out_tex0.st).bgra;
}