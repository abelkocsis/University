#version 430

// pipeline-ból bejövõ per-fragment attribútumok
in vec3 vs_out_pos;

// kimenõ érték - a fragment színe
out vec4 fs_out_col;

uniform int I;
uniform int J;

uniform float red = 0.0;
uniform float green = 1.0;

void main()
{
	fs_out_col = vec4( red , green , I / 256.0 , J / 256.0);
}