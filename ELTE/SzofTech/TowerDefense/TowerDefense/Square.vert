#version 430

vec3 pos[6] = vec3[6](
	vec3(-1,0,-1),
	vec3(-1,0,1),
	vec3(1,0,-1),
	vec3(1,0,1),
	vec3(1,0,-1),
	vec3(-1,0,1)
);

// a pipeline-ban tov�bb adand� �rt�kek
out vec3 vs_out_pos;

// shader k�ls� param�terei - most a h�rom transzform�ci�s m�trixot k�l�n-k�l�n vessz�k �t
uniform mat4 world;
uniform mat4 worldIT;
uniform mat4 MVP;

void main()
{
	gl_Position = (MVP * vec4( pos[gl_VertexID], 1 ));
	vs_out_pos = (world * vec4(pos[gl_VertexID], 1)).xyz;
}