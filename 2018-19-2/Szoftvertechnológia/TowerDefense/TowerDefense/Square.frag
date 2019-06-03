#version 430

// pipeline-b�l bej�v� per-fragment attrib�tumok
in vec3 vs_out_pos;

// kimen� �rt�k - a fragment sz�ne
out vec4 fs_out_col;

uniform int I;
uniform int J;

uniform float red = 0.0;
uniform float green = 1.0;

void main()
{
	fs_out_col = vec4( red , green , I / 256.0 , J / 256.0);
}