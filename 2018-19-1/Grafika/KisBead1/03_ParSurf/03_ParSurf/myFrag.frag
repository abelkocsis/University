#version 130

in vec3 vs_out_col;
in vec3 vs_out_pos;
out vec4 fs_out_col;

void main()
{
	fs_out_col = vec4(vs_out_col, 1);
}

// 1. feladat: rajzoljuk ki fehérrel a téglalapot!

// 2. feladat: uniform változók - az alkalmazás állítsa be, hogy milyen színnel töltsünk ki!

// 3. feladat: rajzoljuk ki az origó középpontú, 1 sugarú kört! Mit kell tenni, ha nem a
//    körlapot, hanem csak a körvonalat akarjuk? Eml.: discard() eldobja a fragmentet

// 4. feladat: komplex számok....
