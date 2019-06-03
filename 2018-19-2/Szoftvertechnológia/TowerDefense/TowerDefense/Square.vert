#version 430

vec3 pos[6] = vec3[6](
	vec3(-1,0,-1),
	vec3(-1,0,1),
	vec3(1,0,-1),
	vec3(1,0,1),
	vec3(1,0,-1),
	vec3(-1,0,1)
);

// a pipeline-ban tovább adandó értékek
out vec3 vs_out_pos;

// shader külsõ paraméterei - most a három transzformációs mátrixot külön-külön vesszük át
uniform mat4 world;
uniform mat4 worldIT;
uniform mat4 MVP;

void main()
{
	gl_Position = (MVP * vec4( pos[gl_VertexID], 1 ));
	vs_out_pos = (world * vec4(pos[gl_VertexID], 1)).xyz;
}