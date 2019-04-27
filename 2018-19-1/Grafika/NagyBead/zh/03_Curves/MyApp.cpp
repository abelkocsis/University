#include "MyApp.h"

#include <math.h>
#include <vector>

#include <array>
#include <list>
#include <tuple>

#include "imgui\imgui.h"

#include "ObjParser_OGL3.h"

CMyApp::CMyApp(void)
{
}


CMyApp::~CMyApp(void)
{
	
}

// Feladat:
// http://cg.elte.hu/~bsc_cg/gyak/mintazh/Sz%C3%A1m%C3%ADt%C3%B3g%C3%A9pes%20grafika%20ZH%20--%20Naprendszer.pdf

void CMyApp::createDisk() {
	std::vector<glm::vec3> vec_pos;
	std::vector<glm::vec3> vec_norm;
	std::vector<glm::vec2> vec_tex;

	// középpont
	vec_pos.push_back(glm::vec3(0, 0, 0));
	vec_norm.push_back(glm::vec3(0, 1, 0));
	vec_tex.push_back(glm::vec2(.5, .5));
	for (int i = 0; i <= N; ++i) {
		float a = -i / (float)N * 2 * M_PI;
		vec_pos.push_back(glm::vec3(cos(a), 0, sin(a)));
		vec_norm.push_back(glm::vec3(0, 1, 0));
		vec_tex.push_back(glm::vec2(cos(a)/2+.5, sin(a) / 2 + .5));
	}

	vbo_disk_pos.BufferData(vec_pos);
	vbo_disk_norm.BufferData(vec_norm);
	vbo_disk_tex.BufferData(vec_tex);

	// geometria VAO-ban való regisztrálása
	m_vao_disk.Init(
		{
			{ CreateAttribute<0, glm::vec3, 0, sizeof(glm::vec3)>, vbo_disk_pos },	// 0-ás attribútum "lényegében" glm::vec3-ak sorozata és az adatok az m_gpuBufferPos GPU pufferben vannak
			{ CreateAttribute<1, glm::vec3, 0, sizeof(glm::vec3)>, vbo_disk_norm },	// 1-es attribútum "lényegében" glm::vec3-ak sorozata és az adatok az m_gpuBufferNormal GPU pufferben vannak
			{ CreateAttribute<2, glm::vec2, 0, sizeof(glm::vec2)>, vbo_disk_tex }	// 2-es attribútum "lényegében" glm::vec2-ők sorozata és az adatok az m_gpuBufferTex GPU pufferben vannak
		}
	);
}

glm::vec3	CMyApp::GetUV(float u, float v)
{
	// origó középpontú, egységsugarú gömb parametrikus alakja: http://hu.wikipedia.org/wiki/G%C3%B6mb#Egyenletek 
	// figyeljünk:	matematikában sokszor a Z tengely mutat felfelé, de nálunk az Y, tehát a legtöbb képlethez képest nálunk
	//				az Y és Z koordináták felcserélve szerepelnek
	u *= 2*3.1415f;
	v *= 3.1415f;
	float cu = cosf(u), su = sinf(u), cv = cosf(v), sv = sinf(v);
	float r = 1;

	return glm::vec3(r*cu*sv, r*cv, r*su*sv);
}

void CMyApp::createGolyo() {
	/*VertexArrayObject m_vao_golyo;
	ArrayBuffer vbo_golyo_pos;
	ArrayBuffer vbo_golyo_norm;
	ArrayBuffer vbo_golyo_tex;
	*/
	std::vector<glm::vec3> vec_pos;
	std::vector<glm::vec3> vec_norm;
	std::vector<glm::vec2> vec_tex;

	
	glm::vec3 atm;
	
	for (int i = 0; i <= NG; ++i)
		for (int j = 0; j <= NG; ++j)
		{
			float u = i / (float)NG;
			float v = j / (float)NG;
			atm = GetUV(u, v);
			float k = atm.x;
			float l = atm.y;
			vec_pos.push_back(atm);
			vec_norm.push_back(glm::vec3(atm.x, atm.y, atm.z));
			vec_tex.push_back(glm::vec2((float)i/(float)NG, (float)j/(float)NG));
			//vert[i + j*(N + 1)].c = glm::normalize(vert[i + j*(N + 1)].p);
		}
	std::vector<short> vec_ind;
	for (int i = 0; i<NG; ++i)
		for (int j = 0; j<NG; ++j)
		{	//megváltoztattam a körbejárási irányt
			vec_ind.push_back((i + 1) + (j)*	(NG + 1));
			vec_ind.push_back( (i)+(j)*	(NG + 1));
			vec_ind.push_back((i)+(j + 1)*(NG + 1));
			
			vec_ind.push_back((i + 1) + (j)*	(NG + 1));
			vec_ind.push_back((i)+(j + 1)*(NG + 1));
			vec_ind.push_back((i + 1) + (j + 1)*(NG + 1));
		}

	/*glm::vec3 atm =glm::vec3(0,0,0);
	for (int i = 0; i <= NG; ++i) {
		float a = -i / (float)NG * 2 * M_PI;
		vec_pos.push_back(atm);
		vec_norm.push_back(atm);
		vec_tex.push_back(atm);*/
		/*for (int j = 0; j <= NG; j++)
		{
			
			float v = i / (float)NG;
			float u = j / (float)NG;
			glm::vec3 atm = GetUV(u, v);

			vec_pos.push_back(atm);
			vec_norm.push_back(glm::vec3(-atm.x, -atm.y, -atm.z));
			vec_tex.push_back(glm::vec2(i / (float)NG, 1));
		}*/
		/*float a = -i / (float)NG * 2 * M_PI;
		vec_pos.push_back(glm::vec3(cos(a), 1, sin(a)));
		vec_norm.push_back(glm::vec3(cos(a), 0, sin(a)));
		vec_tex.push_back(glm::vec2(i / (float)NG, 1));

		
		vec_pos.push_back(glm::vec3(cos(a), 0, sin(a)));
		vec_norm.push_back(glm::vec3(cos(a), 0, sin(a)));
		vec_tex.push_back(glm::vec2(i / (float)N, 0));
		
	}*/

	palastIndices.BufferData(vec_ind);
	vbo_golyo_pos.BufferData(vec_pos);
	vbo_golyo_norm.BufferData(vec_norm);
	vbo_golyo_tex.BufferData(vec_tex);

	// geometria VAO-ban való regisztrálása
	m_vao_golyo.Init(
	{
		{ CreateAttribute<0, glm::vec3, 0, sizeof(glm::vec3)>, vbo_golyo_pos },	// 0-ás attribútum "lényegében" glm::vec3-ak sorozata és az adatok az m_gpuBufferPos GPU pufferben vannak
		{ CreateAttribute<1, glm::vec3, 0, sizeof(glm::vec3)>, vbo_golyo_norm },	// 1-es attribútum "lényegében" glm::vec3-ak sorozata és az adatok az m_gpuBufferNormal GPU pufferben vannak
		{ CreateAttribute<2, glm::vec2, 0, sizeof(glm::vec2)>, vbo_golyo_tex }	// 2-es attribútum "lényegében" glm::vec2-ők sorozata és az adatok az m_gpuBufferTex GPU pufferben vannak
	},
		palastIndices
	);
}

void CMyApp::createPalast() {
	std::vector<glm::vec3> vec_pos;
	std::vector<glm::vec3> vec_norm;
	std::vector<glm::vec2> vec_tex;

	for (int i = 0; i <= N; ++i) {
		float a = -i / (float)N * 2 * M_PI;
		vec_pos.push_back(glm::vec3(cos(a), 1, sin(a)));
		vec_norm.push_back(glm::vec3(cos(a), 0, sin(a)));
		vec_tex.push_back(glm::vec2(i / (float)N, 1));

		vec_pos.push_back(glm::vec3(cos(a), 0, sin(a)));
		vec_norm.push_back(glm::vec3(cos(a), 0, sin(a)));
		vec_tex.push_back(glm::vec2(i / (float)N, 0));
	}

	vbo_palast_pos.BufferData(vec_pos);
	vbo_palast_norm.BufferData(vec_norm);
	vbo_palast_tex.BufferData(vec_tex);

	// geometria VAO-ban való regisztrálása
	m_vao_palast.Init(
		{
			{ CreateAttribute<0, glm::vec3, 0, sizeof(glm::vec3)>, vbo_palast_pos },	// 0-ás attribútum "lényegében" glm::vec3-ak sorozata és az adatok az m_gpuBufferPos GPU pufferben vannak
			{ CreateAttribute<1, glm::vec3, 0, sizeof(glm::vec3)>, vbo_palast_norm },	// 1-es attribútum "lényegében" glm::vec3-ak sorozata és az adatok az m_gpuBufferNormal GPU pufferben vannak
			{ CreateAttribute<2, glm::vec2, 0, sizeof(glm::vec2)>, vbo_palast_tex }	    // 2-es attribútum "lényegében" glm::vec2-ők sorozata és az adatok az m_gpuBufferTex GPU pufferben vannak
		}
	);
}

void CMyApp::createAkadaly() {
	std::vector<glm::vec3> vec_pos;
	std::vector<glm::vec3> vec_norm;
	std::vector<glm::vec2> vec_tex;

	
	vec_pos.push_back(glm::vec3(0, 0, 0));
	vec_pos.push_back(glm::vec3(1, 0, 0));
	vec_pos.push_back(glm::vec3(1, 0, 1));
	vec_pos.push_back(glm::vec3(0, 0, 1));
	vec_pos.push_back(glm::vec3(0, 1, 0));
	vec_pos.push_back(glm::vec3(1, 1, 0));
	vec_pos.push_back(glm::vec3(1, 1, 1));
	vec_pos.push_back(glm::vec3(0, 1, 1));
	vec_pos.push_back(glm::vec3(0, 0, 0));
	vec_pos.push_back(glm::vec3(1, 0, 0));
	vec_pos.push_back(glm::vec3(1, 0, 1));
	vec_pos.push_back(glm::vec3(0, 0, 1));
	vec_pos.push_back(glm::vec3(0, 1, 0));
	vec_pos.push_back(glm::vec3(1, 1, 0));
	vec_pos.push_back(glm::vec3(1, 1, 1));
	vec_pos.push_back(glm::vec3(0, 1, 1));
	vec_pos.push_back(glm::vec3(0, 1, 0));
	vec_pos.push_back(glm::vec3(1, 1, 0));
	vec_pos.push_back(glm::vec3(1, 1, 1));
	vec_pos.push_back(glm::vec3(0, 1, 1));

	vec_norm.push_back(glm::vec3(0,0,-1));//0
	vec_norm.push_back(glm::vec3(0, 0, -1));
	vec_norm.push_back(glm::vec3(0, 0, 1));
	vec_norm.push_back(glm::vec3(0, 0, 1));
	vec_norm.push_back(glm::vec3(0, 0, -1));
	vec_norm.push_back(glm::vec3(0, 0, -1));//5
	vec_norm.push_back(glm::vec3(0, 0, 1));
	vec_norm.push_back(glm::vec3(0, 0, 1));//7
	vec_norm.push_back(glm::vec3(-1, 0, 0));
	vec_norm.push_back(glm::vec3(1, 0, 0));
	vec_norm.push_back(glm::vec3(1, 0, 0));//10
	vec_norm.push_back(glm::vec3(-1, 0, 0));//11
	vec_norm.push_back(glm::vec3(-1, 0, 0));
	vec_norm.push_back(glm::vec3(1, 0, 0)); //13
	vec_norm.push_back(glm::vec3(1, 0, 0));
	vec_norm.push_back(glm::vec3(-1, 0, 0));//15
	vec_norm.push_back(glm::vec3(0, 1, 0));
	vec_norm.push_back(glm::vec3(0, 1, 0));
	vec_norm.push_back(glm::vec3(0, 1, 0));
	vec_norm.push_back(glm::vec3(0, 1, 0));

	vec_tex.push_back(glm::vec2(0, 0));//0
	vec_tex.push_back(glm::vec2(1, 0));//1
	vec_tex.push_back(glm::vec2(0, 0));//2
	vec_tex.push_back(glm::vec2(1, 0));//3
	vec_tex.push_back(glm::vec2(0, 1));//4
	vec_tex.push_back(glm::vec2(1, 1));//5
	vec_tex.push_back(glm::vec2(0, 1));//6
	vec_tex.push_back(glm::vec2(1, 1));//7
	vec_tex.push_back(glm::vec2(1, 0));//8
	vec_tex.push_back(glm::vec2(0, 0));//9
	vec_tex.push_back(glm::vec2(1, 0));//10
	vec_tex.push_back(glm::vec2(0, 0));//11/
	vec_tex.push_back(glm::vec2(1, 1));//12/
	vec_tex.push_back(glm::vec2(0, 1));//13
	vec_tex.push_back(glm::vec2(1, 1));//14
	vec_tex.push_back(glm::vec2(0, 1));//15
	vec_tex.push_back(glm::vec2(0, 0));//16
	vec_tex.push_back(glm::vec2(1, 0));//17
	vec_tex.push_back(glm::vec2(1, 1));//18
	vec_tex.push_back(glm::vec2(0, 1));//19

	std::vector<short> vec_ind;

	vec_ind = {
		0,4,1,
		1,4,5,
		9,13,10,
		10,13,14,
		2,6,3,
		3,6,7,
		11,15,8,
		8,15,12,
		16,19,17,
		17,15,18
	};
	akadalyIndices.BufferData(vec_ind);
	vbo_akadaly_pos.BufferData(vec_pos);
	vbo_akadaly_norm.BufferData(vec_norm);
	vbo_akadaly_tex.BufferData(vec_tex);

	// geometria VAO-ban való regisztrálása
	m_vao_akadaly.Init(
	{
		{ CreateAttribute<0, glm::vec3, 0, sizeof(glm::vec3)>, vbo_akadaly_pos },	// 0-ás attribútum "lényegében" glm::vec3-ak sorozata és az adatok az m_gpuBufferPos GPU pufferben vannak
		{ CreateAttribute<1, glm::vec3, 0, sizeof(glm::vec3)>, vbo_akadaly_norm },	// 1-es attribútum "lényegében" glm::vec3-ak sorozata és az adatok az m_gpuBufferNormal GPU pufferben vannak
		{ CreateAttribute<2, glm::vec2, 0, sizeof(glm::vec2)>, vbo_akadaly_tex }	// 2-es attribútum "lényegében" glm::vec2-ők sorozata és az adatok az m_gpuBufferTex GPU pufferben vannak
	},
		akadalyIndices
	);
}

bool CMyApp::Init()
{

	// törlési szín legyen fehér
	glClearColor(1,1,1, 1);

	glEnable(GL_CULL_FACE); // kapcsoljuk be a hatrafele nezo lapok eldobasat
	glEnable(GL_DEPTH_TEST); // mélységi teszt bekapcsolása (takarás)
	//glDepthMask(GL_FALSE); // kikapcsolja a z-pufferbe történő írást - https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glDepthMask.xml

	glLineWidth(4.0f); // a vonalprimitívek vastagsága: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glLineWidth.xhtml
	//glEnable(GL_LINE_SMOOTH);

	// átlátszóság engedélyezése
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // meghatározza, hogy az átlátszó objektum az adott pixelben hogyan módosítsa a korábbi fragmentekből oda lerakott színt: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBlendFunc.xhtml

	// a raszterizált pontprimitívek mérete
	glPointSize(15.0f);

	//
	// shaderek betöltése
	//

	// így is létre lehetne hozni:

	// a shadereket tároló program létrehozása
	m_program.Init({ 
		{ GL_VERTEX_SHADER, "myVert.vert"},
		{ GL_FRAGMENT_SHADER, "myFrag.frag"}
	},
	{ 
		{ 0, "vs_in_pos" },					// VAO 0-as csatorna menjen a vs_in_pos-ba
		{ 1, "vs_in_normal" },				// VAO 1-es csatorna menjen a vs_in_normal-ba
		{ 2, "vs_out_tex0" },				// VAO 2-es csatorna menjen a vs_in_tex0-ba
	});

	m_program.LinkProgram();

	// tengelyeket kirajzoló shader rövid inicializálása
	m_axesProgram.Init({
		{GL_VERTEX_SHADER, "axes.vert"},
		{GL_FRAGMENT_SHADER, "axes.frag"}
	});
	// haladóknak, még rövidebb: 
	//m_axesProgram.Init({"axes.vert"_vs, "axes.frag"_fs});

	// kontrollpontokat kirajzoló program
	m_pointProgram.Init({
		{ GL_VERTEX_SHADER, "pointDrawer.vert" },
		{ GL_FRAGMENT_SHADER, "pointDrawer.frag" }
	});

	//
	// geometria definiálása (std::vector<...>) és GPU pufferekbe (m_buffer*) való feltöltése BufferData-val
	//

	createDisk();
	createPalast();
	createGolyo();
	createAkadaly();

	// vertexek pozíciói:
	/*
	Az m_gpuBufferPos konstruktora már létrehozott egy GPU puffer azonosítót és a most következő BufferData hívás ezt 
		1. bind-olni fogja GL_ARRAY_BUFFER target-re (hiszen m_gpuBufferPos típusa ArrayBuffer) és
		2. glBufferData segítségével áttölti a GPU-ra az argumentumban adott tároló értékeit

	*/
	m_gpuBufferPos.BufferData( 
		std::vector<glm::vec3>{
			//		  X, Y, Z
			/*glm::vec3(-10,-1, -10),
			glm::vec3(-10,-1,  10), 
			glm::vec3( 10,-1, -10),
			glm::vec3( 10,-1,  10) */
			glm::vec3(-10, -1, -10), //0
			glm::vec3(-10, -1, 0),
			glm::vec3(0, -1, -10),
			glm::vec3(-3, -1, -3), //3
			glm::vec3(0, -1, -3),
			glm::vec3(-3, -1, 0),
			glm::vec3(10, -1, -10), //6
			glm::vec3(0, -1, 0),
			glm::vec3(10, -1, 0), //8
			glm::vec3(-10, -1, 10),
			glm::vec3(0, -1, 10),
			glm::vec3(4, -1, 4), //11
			glm::vec3(7, -1, 4), 
			glm::vec3(7, -1, 7), //13
			glm::vec3(4, -1, 7),
			glm::vec3(10, -1, 10),//15

		}
	);

	// normálisai
	m_gpuBufferNormal.BufferData(
		std::vector<glm::vec3>{
			// normal.X,.Y,.Z
			/*glm::vec3(0, 1, 0), // 0-ás csúcspont
			glm::vec3(0, 1, 0), // 1-es
			glm::vec3(0, 1, 0), // 2-es
			glm::vec3(0, 1, 0)  // 3-as*/
			glm::vec3(0, 1, 0), // 0-es
			glm::vec3(0, 1, 0), // 1-es
			glm::vec3(0, 1, 0),  // 2-as
			glm::vec3(0, 1, 0),  // 3-as
			glm::vec3(0, 1, 0),  // 3-as
			glm::vec3(0, 1, 0),  // 3-as
			glm::vec3(0, 1, 0),  // 3-as
			glm::vec3(0, 1, 0),  // 3-as
			glm::vec3(0, 1, 0),	//8
				glm::vec3(0, 1, 0),	//8
				glm::vec3(0, 1, 0),	//8
				glm::vec3(0, 1, 0),	//8
				glm::vec3(0, 1, 0),	//8
				glm::vec3(0, 1, 0),	//8
				glm::vec3(0, 1, 0),	//8
				glm::vec3(0, 1, 0)	//15
		}
	);

	// textúrakoordinátái
	m_gpuBufferTex.BufferData(
		std::vector<glm::vec2>{
			//        u, v
			/*glm::vec2(0, 0), // 0-ás csúcspont
			glm::vec2(1, 0), // 1-es
			glm::vec2(0, 1), // 2-es
			glm::vec2(1, 1)	 // 3-as*/
			glm::vec2(0, 0), //0
			glm::vec2(0, 0.5),
			glm::vec2(0.5, 0),  //2
			glm::vec2(0.35, 0.35),	 //3
			glm::vec2(0.5, 0.35), 
			glm::vec2(0.35, 0.5), //5
			glm::vec2(1, 0), 
			glm::vec2(0.5, 0.5), 
			glm::vec2(1, 0.5), //8
				glm::vec2(0, 1), //9
				glm::vec2(0.5, 1), //10
				glm::vec2(0.7, 0.7), //11
				glm::vec2(0.85, 0.7), //12
				glm::vec2(0.85, 0.85), //13
				glm::vec2(0.7, 0.8), //14
				glm::vec2(1, 1) //15
		}
	);

	// és a primitíveket alkotó csúcspontok indexei (az előző tömbökből) - triangle list-el való kirajzolásra felkészülve
	m_gpuBufferIndices.BufferData(
		std::vector<int>{
			/*0,1,2,	// 1. háromszög: 0-1-2 csúcspontokból
			2,1,3	// 2. háromszög: 2-1-3 csúcspontokból*/
			0,1,2,
				2,1,3,
				2,3,4,
				3,1,5,
				2,7,6,
				6,7,8,
				1,9,7,
				7,9,10,
				7,10,14,
				7,14,11,
				14,10,13,
				13,10,15,
				8,13,15,
				8,12,13,
				8,11,12,
				7,11,8
		}
	);

	// geometria VAO-ban való regisztrálása
	m_vao.Init(
		{
			{ CreateAttribute<0, glm::vec3, 0, sizeof(glm::vec3)>, m_gpuBufferPos },	// 0-ás attribútum "lényegében" glm::vec3-ak sorozata és az adatok az m_gpuBufferPos GPU pufferben vannak
			{ CreateAttribute<1, glm::vec3, 0, sizeof(glm::vec3)>, m_gpuBufferNormal },	// 1-es attribútum "lényegében" glm::vec3-ak sorozata és az adatok az m_gpuBufferNormal GPU pufferben vannak
			{ CreateAttribute<2, glm::vec2, 0, sizeof(glm::vec2)>, m_gpuBufferTex }		// 2-es attribútum "lényegében" glm::vec2-ők sorozata és az adatok az m_gpuBufferTex GPU pufferben vannak
		},
		m_gpuBufferIndices
	);

	// textúra betöltése
	m_textureMetal.FromFile("texture.png");
	m_texturEarth.FromFile("earth.png"); 
	m_texturScales.FromFile("scales.jpg");
	m_texturShell.FromFile("shell.jpg");
	// mesh betöltése
	m_mesh = ObjParser::parse("suzanne.obj");

	// kamera
	m_camera.SetProj(45.0f, 640.0f / 480.0f, 0.01f, 1000.0f);

	srand(time(NULL));
	// labdák létrehozása
	float atmx, atmz;
	balls.resize(x);
	for (int i = 0; i < x; i++)
	{
		bool rossz = true;
		while (rossz) {
			atmx = rand() % 18 - 9;
			atmz = rand() % 18 - 9;
			rossz = false;
			for (int j = 0; j < i; j++)
			{
				if (sqrt(pow((balls[j].x - atmx), 2) + pow((balls[j].z - atmz), 2)) < 2) {
					rossz = true;
					break;
				}
					
			}
		}
		balls[i].x = atmx;
		balls[i].z = atmz;
		balls[i].m = rand() % 3 + 1;
		balls[i].velocy.x = (((rand() % 50) / (float)49)*2 - 1)/4;
		balls[i].velocy.z = (((rand() % 50) / (float)49)*2 - 1)/4;
		balls[i].lastMove = SDL_GetTicks();
	}
	balls[0].lastMove = SDL_GetTicks();
	balls[0].velocy.x = 0;
	balls[0].velocy.z = 0;
	balls[0].m = 3;

	eye.y = 15;

	startTime = SDL_GetTicks();
	glm::vec3 at = glm::vec3(balls[0].x, 0, balls[0].z);
	m_camera.SetView(eye, at, glm::vec3(0,1,0));

	last_time_3 = SDL_GetTicks();
	last_time_2 = SDL_GetTicks();
	last_akadaly = SDL_GetTicks();

	return true;
}

void CMyApp::Clean()
{
}

bool CMyApp::utkozes(int i, int j) {
	ball a = balls[i];
	ball b = balls[j];
	return (sqrt((a.x-b.x)*(a.x-b.x)+ (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z)) <= 2);
}

void CMyApp::golyoUtkozes(int i) {
	for (int j = 0; j < balls.size(); j++)
	{
		if (i != j && balls[j].active && !balls[j].zuhan && utkozes(i, j)) {
			ball a = balls[i];
			ball b = balls[j];
			float atm;

			if (a.velocy.x == 0)
				a.velocy.x = 0.001;
			if (a.velocy.z == 0)
				a.velocy.z = 0.001;
			if (b.velocy.x == 0)
				b.velocy.x = 0.001;
			if (b.velocy.z == 0)
				b.velocy.z = 0.001;

			a.velocy *= a.m;
			b.velocy *= b.m;

			glm::vec3 kozepvonal = glm::vec3(a.x - b.x, 0, a.z - b.z);
			kozepvonal = kozepvonal/glm::length(kozepvonal);
			glm::vec3 v11, v12, v21, v22;
			float alfa, beta, gamma;

			alfa = atan(a.velocy.z / a.velocy.x);
			beta = atan(kozepvonal.z / kozepvonal.x);
			gamma = M_PI + alfa - beta; //ez a sor a kérdéses
			v21 = kozepvonal*cos(gamma)*glm::length(a.velocy);
			v11 = glm::vec3(-kozepvonal.z, 0, kozepvonal.x)*sqrt(pow(glm::length(a.velocy), 2) - pow(glm::length(v21), 2));
			//v21 = glm::reflect(a.velocy, kozepvonal);
			//v11 = glm::reflect(b.velocy, kozepvonal);

			kozepvonal = glm::vec3(b.x - a.x, 0, b.z - a.z);
			kozepvonal = kozepvonal / glm::length(kozepvonal);
			alfa = atan(b.velocy.z / b.velocy.x);
			beta = atan(kozepvonal.z / kozepvonal.x);
			gamma = M_PI + alfa - beta; //ez a sor a kérdéses
			v12 = kozepvonal*cos(gamma)*glm::length(b.velocy);
			float ab = pow(glm::length(b.velocy), 2);
			float bb = pow(glm::length(v12), 2);
			v22 = glm::vec3(-kozepvonal.z, 0, kozepvonal.x)*sqrt(pow(glm::length(b.velocy), 2) - pow(glm::length(v12), 2));
			//v12 = glm::reflect(a.velocy, kozepvonal);
			//v22 = glm::reflect(b.velocy, kozepvonal);
			
			a.velocy = v11 + v12;
			b.velocy = v21 + v22;
			a.velocy /= a.m;
			b.velocy /= b.m;
			
			a.x += a.velocy.x;
			a.z += a.velocy.z;
			b.x += b.velocy.x;
			b.z += b.velocy.z;

			


			//idáig
			balls[i] = a;
			balls[j] = b;
		}
	}
}

void CMyApp::akadalyHappen() {
	int a = rand() % 3;
	int melyik;
	if (a < 2)
		for (int i = 0; i < 5; i++)
		{
			if (akadalyok[i].active) {
				akadaly ak = akadalyok[i];
				if (a == 0)
					ak.active = false;
				else
				{
					float x, z;
					bool rossz = true;
					while (rossz) {
						x = rand() % 18 - 9;
						z = rand() % 18 - 9;
						rossz = false;
						for (int j = 0; j < balls.size(); j++)
						{
							if (sqrt(pow((balls[j].x - x), 2) + pow((balls[j].z - z), 2)) < 2.5) {
								rossz = true;
								break;
							}

						}
					}
					ak.x = x;
					ak.z = z;
					ak.utkozes = 0;
					akadalyok[i] = ak;
				}
				break;
			}
		}
	else {
		for (int i = 0; i < 5; i++)
		{
			if (!akadalyok[i].active) {
				akadaly ak;
				ak.active = true;
				float x, z;
				bool rossz = true;
				while (rossz) {
					x = rand() % 18 - 9;
					z = rand() % 18 - 9;
					rossz = false;
					for (int j = 0; j < balls.size(); j++)
					{
						if (sqrt(pow((balls[j].x - x), 2) + pow((balls[j].z - z), 2)) < 2.5) {
							rossz = true;
							break;
						}

					}
				}
				ak.utkozes = 0;
				ak.x = x;
				ak.z = z;
				akadalyok[i] = ak;
				break;

			}
		}
	}
}

void CMyApp::akadalyUtkozes(int i) {
	for (int j = 0; j < 5; j++)
	{
		if (akadalyok[j].active) {
			ball g = balls[i];
			akadaly ak = akadalyok[j];
			if (g.x > ak.x - 1 && g.x < ak.x + 2 && g.z > ak.z - 1 && g.z < ak.z + 2 && glm::length(glm::vec3(ak.x + 0.5 - g.x, 0, ak.z + 0.5 - g.z))<1.7) {
				ak.utkozes++;
				if (abs(ak.x + 0.5 - g.x) > abs(ak.z + 0.5 - g.z)) {
					if (g.velocy.x > 0) {
						g.x = ak.x - ((ak.x - g.x)) -seged;//balrol megy neki
					}
					else {
						g.x = (ak.x+1) - ((ak.x+1 - g.x)) + seged; //jobbrol megy neki
					}
					g.velocy.x *= -1;
				}
				else {
					if (g.velocy.z > 0) {
						g.z = ak.z - ((ak.z - g.z)) -seged; //negatív irányból megy neki
					}
					else {
						g.z = (ak.z + 1) - ((ak.z + 1) - g.z) + seged;
					}
					g.velocy.z *= -1;
				}
			}
			if (ak.utkozes > 10) {
				ak.active = false;
			}
			balls[i] = g;
			akadalyok[j] = ak;
		}
	}
}

void CMyApp::falUtkozes(int i) {
	if (balls[i].x > 9) {
		balls[i].x = 9 - (9 - balls[i].x) - seged/2;
		balls[i].velocy.x *= -1;
	}
	if (balls[i].z > 9) {
		balls[i].z = 9 - (9 - balls[i].z) - seged/2;
		balls[i].velocy.z *= -1;
	}
	if (balls[i].x < -9) {
		balls[i].x = -9 + (-9 - balls[i].x) + seged/2;
		balls[i].velocy.x *= -1;
	}
	if (balls[i].z < -9) {
		balls[i].z = -9 + (-9 - balls[i].z) + seged/2;
		balls[i].velocy.z *= -1;
	}

}

void CMyApp::inHole(int i) {
	ball a = balls[i];
	if ((a.x > -3 && a.x < 0 && a.z < 0 && a.z > -3)) {
		a.zuhan = true;
		a.velocy.x = (-1.5 - a.x)/20;
		a.velocy.z = (-1.5 - a.z)/20;
	}
	if ((a.x > 4 && a.x < 7 && a.z < 7 && a.z > 4)) {
		a.zuhan = true;
		a.velocy.x = (5.5 - a.x)/20;
		a.velocy.z = (5.5 - a.z)/20;
	}
		
	balls[i] = a;
}

void CMyApp::newBalls() {
		ball a, b;
		float atmx, atmz;
		bool rossz = true;
		while (rossz) {
			atmx = rand() % 18 - 9;
			atmz = rand() % 18 - 9;
			rossz = false;
			for (int j = 0; j < balls.size(); j++)
			{
				if (sqrt(pow((balls[j].x - atmx), 2) + pow((balls[j].z - atmz), 2)) < 2) {
					rossz = true;
					break;
				}

			}
			for (int j = 0; j < 5; j++)
			{
				if (akadalyok[j].active && glm::length(glm::vec3(akadalyok[j].x - atmx, 0, akadalyok[j].z - atmz)) < 3) {
					rossz = true;
					break;
				}
			}
		}
		a.x = atmx;
		a.z = atmz;
		a.y = 10;
		a.lastMove = SDL_GetTicks();
		a.m = rand() % 3 + 1;
		a.velocy.x = (((rand() % 50) / (float)49) * 2 - 1) / 4;
		a.velocy.z = (((rand() % 50) / (float)49) * 2 - 1) / 4;
		a.uj = true;
		balls.push_back(a);
		rossz = true;
		while (rossz) {
			atmx = rand() % 18 - 9;
			atmz = rand() % 18 - 9;
			rossz = false;
			for (int j = 0; j < balls.size(); j++)
			{
				if (sqrt(pow((balls[j].x - atmx), 2) + pow((balls[j].z - atmz), 2)) < 2) {
					rossz = true;
					break;
				}
				for (int j = 0; j < 5; j++)
				{
					if (akadalyok[j].active && glm::length(glm::vec3(akadalyok[j].x - atmx, 0, akadalyok[j].z - atmz)) < 3) {
						rossz = true;
						break;
					}
				}

			}
		}
		b.x = atmx;
		b.z = atmz;
		b.y = 10;
		b.lastMove = SDL_GetTicks();
		b.m = rand() % 3 + 1;
		b.velocy.x = (((rand() % 50) / (float)49) * 2 - 1) / 4;
		b.velocy.z = (((rand() % 50) / (float)49) * 2 - 1) / 4;
		b.uj = true;
		balls.push_back(b);
	
}

void CMyApp::Update()
{
	currentTime = SDL_GetTicks();
	static Uint32 last_time = SDL_GetTicks();
	float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;
	float delta_time_2 = (SDL_GetTicks() - last_time_2) / 1000.0f;
	float delta_time_3 = (SDL_GetTicks() - last_time_3) / 1000.0f;
	m_camera.Update(delta_time);

	if ((currentTime - last_akadaly) / 1000 > 1) {
		last_akadaly = currentTime;
		akadalyHappen();
	}
	

	last_time = SDL_GetTicks();

	if (delta_time_2 > 0.001) {
		userEnabled = false;
		if (balls[0].active) {
			if (!pressedx) {
				if (abs(balls[0].velocy.x) < d * g * balls[0].m)
					balls[0].velocy.x = 0;
				else if (balls[0].velocy.x > 0)
					balls[0].velocy.x -= d*g*balls[0].m;
				else
					balls[0].velocy.x += d * g * balls[0].m;
			}
			if (!pressedz) {
				if (abs(balls[0].velocy.z) < d * g* balls[0].m)
					balls[0].velocy.z = 0;
				else if (balls[0].velocy.z > 0)
					balls[0].velocy.z -= d * g* balls[0].m;
				else
					balls[0].velocy.z += d * g * balls[0].m;
			}
			pressedx = false;
			pressedz = false;
			if ( balls[0].zuhan) {
				if (balls[0].y < -500)
					balls[0].active = false;
				balls[0].velocy.y += 0.05;
				balls[0].y -= balls[0].velocy.y;
			}
			
		}
			
		

		
		for (int i = 0; i < balls.size(); i++)
		{
			if (!balls[i].uj) {
				balls[i].x += balls[i].velocy.x;
				balls[i].z += balls[i].velocy.z;
				if (canIDie || !i==0)
					inHole(i);
			}

			
			if (balls[i].active && !balls[i].zuhan && !balls[i].uj) {
				falUtkozes(i);
				golyoUtkozes(i);
				akadalyUtkozes(i);

				if (glm::length(balls[i].velocy) > 0)
					balls[i].lastMove = SDL_GetTicks();
				else if ((SDL_GetTicks() - balls[i].lastMove) / 1000 > 5) {
					balls[i].sullyedes = true;
					balls[i].lastMove = SDL_GetTicks();
				}
					

			
				if (i != 0 || !pressedx)
					if (abs(balls[i].velocy.x) <d * g * balls[i].m)
						balls[i].velocy.x = 0;
					else if (balls[i].velocy.x > 0)
						balls[i].velocy.x -= d*g*balls[i].m;
					else
						balls[i].velocy.x += d * g * balls[i].m;
				
				if (i != 0 || !pressedz)
					if (abs(balls[i].velocy.z) < d * g* balls[i].m)
						balls[i].velocy.z = 0;
					else if (balls[i].velocy.z > 0)
						balls[i].velocy.z -= d * g* balls[i].m;
					else
						balls[i].velocy.z += d * g * balls[i].m;
				







			
				
				balls[i].axis = glm::vec3(balls[i].velocy.z, 0, -balls[i].velocy.x);
				
					
				float ax = (float)glm::length(balls[i].velocy)* delta_time_2*M_PI*M_PI*1.5; // / ball radius
				if (!(balls[i].velocy.x == 0 && balls[i].velocy.z == 0))
					balls[i].status = glm::mat4(glm::rotate(ax, balls[i].axis)*balls[i].last_rotate);
			
				
					}
			/*
				float ax = (float)glm::length(balls[i].velocy)* delta_time_2*M_PI*M_PI;
				balls[i].status = glm::rotate(ax, balls[i].status);*/






			if (balls[i].active && balls[i].zuhan && !balls[i].uj) {
				if (balls[i].y < -500)
					balls[i].active = false;
				balls[i].velocy.y += 0.05;
				balls[i].y -= balls[i].velocy.y;
			}
			if (balls[i].uj) {
				balls[i].velocy.y += 0.05;
				balls[i].y -= balls[i].velocy.y;
				if (balls[i].y <= 0) {
					balls[i].y = 1;
					balls[i].velocy.y = 0;
					balls[i].uj = false;
				}

			}
			if (balls[i].sullyedes) {
				balls[i].y = 1 - (SDL_GetTicks()-balls[i].lastMove)*2/1000;
				if (balls[i].y < -1)
					balls[i].active = false;
			}
			

		}
		pressedx = false;
		pressedz = false;
		last_time_2 = SDL_GetTicks();
		userEnabled = true;
	}

	if (delta_time_3 > 2) {
		newBalls();
		last_time_3 = SDL_GetTicks();
		}
		
	}
	


void CMyApp::drawDisk(const glm::mat4& discWorld) {
	m_program.SetUniform("world", discWorld);
	m_program.SetUniform("worldIT", glm::transpose(glm::inverse(discWorld)));
	m_program.SetUniform("MVP", m_camera.GetViewProj()*discWorld);
	m_program.SetUniform("Kd", glm::vec4(1, 1, 1, 1));
	m_vao_disk.Bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, N + 2);
}
void CMyApp::drawCylidner(const glm::mat4& palastWorld) {
	m_program.SetUniform("world", palastWorld);
	m_program.SetUniform("worldIT", glm::transpose(glm::inverse(palastWorld)));
	m_program.SetUniform("MVP", m_camera.GetViewProj()*palastWorld);
	m_program.SetUniform("Kd", glm::vec4(1, 1, 1, 1));
	m_vao_palast.Bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * N + 2);

	drawDisk(palastWorld*glm::translate(glm::vec3(0, 1, 0)));
	drawDisk(palastWorld*glm::rotate<float>(M_PI, glm::vec3(1, 0, 0)));
}

void  CMyApp::drawGolyo(const glm::mat4& golyoWorld) {
	m_program.SetUniform("world", golyoWorld);
	m_program.SetUniform("worldIT", glm::transpose(glm::inverse(golyoWorld)));
	m_program.SetUniform("MVP", m_camera.GetViewProj()*golyoWorld);
	m_program.SetUniform("Kd", glm::vec4(1, 1, 1, 1));
	m_vao_golyo.Bind();
	//glDrawArrays(GL_TRIANGLE_FAN, 0, NG * NG + NG);
	
	glDrawElements(	GL_TRIANGLES,		// primitív típus
					3 * 2 * (NG)*(NG),		// hany csucspontot hasznalunk a kirajzolashoz
					GL_UNSIGNED_SHORT,	// indexek tipusa
					0);					// indexek cime
					
	/*									// VAO kikapcsolasa
	glBindVertexArray(0);

	// shader kikapcsolasa
	glUseProgram(0);*/
}
void  CMyApp::drawAkadaly(const glm::mat4& golyoWorld) {
	m_program.SetUniform("world", golyoWorld);
	m_program.SetUniform("worldIT", glm::transpose(glm::inverse(golyoWorld)));
	m_program.SetUniform("MVP", m_camera.GetViewProj()*golyoWorld);
	m_program.SetUniform("Kd", glm::vec4(1, 1, 1, 1));
	m_vao_akadaly.Bind();
	//glDrawArrays(GL_TRIANGLE_FAN, 0, NG * NG + NG);

	glDrawElements(GL_TRIANGLES,		// primitív típus
		10*3,		// hany csucspontot hasznalunk a kirajzolashoz
		GL_UNSIGNED_SHORT,	// indexek tipusa
		0);					// indexek cime

							/*									// VAO kikapcsolasa
							glBindVertexArray(0);

							// shader kikapcsolasa
							glUseProgram(0);*/
}

void CMyApp::Render()
{
	userEnabled = false;
	// töröljük a frampuffert (GL_COLOR_BUFFER_BIT) és a mélységi Z puffert (GL_DEPTH_BUFFER_BIT)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// tengelyek
	//m_axesProgram.Use();
	if (balls[0].active)
		m_axesProgram.SetUniform("ball_active", 1);
	else
		m_axesProgram.SetUniform("ball_active", 0);
	
	m_camera.SetView(eye, m_camera.GetAt()+atChange, m_camera.GetUp());
	eye = m_camera.GetEye();
	if (eye.x != 0)
		int asd = 0;
	
	atChange = glm::vec3(0, 0, 0);
	m_axesProgram.SetUniform("mvp", m_camera.GetViewProj()*glm::translate(glm::vec3(0,0.1f,0)));

	glDrawArrays(GL_LINES, 0, 6);

	// kontrollpontok
	m_pointProgram.Use();

	
	
	//m_pointProgram.SetUniform("mvp", m_camera.GetViewProj());
	//m_pointProgram.SetUniform("points", m_controlPoints);
	//m_pointProgram.SetUniform("color", glm::vec4(1,0,1,1));

	//glDrawArrays(GL_POINTS, 0, (GLsizei)m_controlPoints.size());

	// kontrollpontokat összekötő szakaszok
	//m_pointProgram.SetUniform("color", glm::vec4(0.5, 0.5, 0.5, 1));
	//glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)m_controlPoints.size());

	// mindegyik geometria ugyanazt a shader programot hasznalja: ne kapcsolgassuk most ki-be
	m_program.Use();

	m_program.SetTexture("texImage", 0, m_textureMetal);
	
	float fx = sin((currentTime-startTime)*2*M_PI/5000) * 10;
	float fz = cos((currentTime - startTime) * 2 * M_PI/5000) * 10;
	m_axesProgram.SetUniform("eye_pos", eye);
	m_program.SetUniform("eye_pos", eye);
	if (balls[0].active && !balls[0].zuhan) {
		m_program.SetUniform("light2_active", 1);
	}
	else {
		m_program.SetUniform("light2_active", 0);
	}
	
	m_program.SetUniform("light_pos", glm::vec3((float)fx, (float)5, (float)fz));
	m_program.SetUniform("light_pos2", glm::vec3(balls[0].x, balls[0].y, balls[0].z));
	//m_program.SetUniform("light_pos2", glm::vec3(1, 10, 10));
	// talaj
	glm::mat4 wallWorld = glm::translate(glm::vec3(0, 1, 0));
	m_program.SetUniform("world", wallWorld);
	m_program.SetUniform("worldIT", glm::transpose(glm::inverse(wallWorld)));
	m_program.SetUniform("MVP", m_camera.GetViewProj()*wallWorld);
	m_program.SetUniform("Kd", glm::vec4(1,1,1, 1));

	m_vao.Bind();
	glDrawElements(GL_TRIANGLES, 3*16, GL_UNSIGNED_INT, 0);
	m_vao.Unbind(); // nem feltétlen szükséges: a m_mesh->draw beállítja a saját VAO-ját



	// henger
	m_program.SetTexture("texImage", 0, m_texturScales);

	//pálya szélének kirajzolása
	//drawCilinderben: glm::translate(glm::vec3(2, 4, 0))*glm::rotate<float>(alpha, glm::vec3(0,0,1))*glm::scale<float>(glm::vec3(.25, 1, .25))
	drawCylidner(glm::translate(glm::vec3(10, 0, -10))*glm::rotate<float>(M_PI /2 , glm::vec3(1, 0, 0))*glm::rotate<float>(M_PI / 4, glm::vec3(0, 1, 0))*glm::scale<float>(glm::vec3(.25, 20, .25)));
	drawCylidner(glm::translate(glm::vec3(10, 0, -10))*glm::rotate<float>(M_PI / 2, glm::vec3(0, 0, 1))*glm::rotate<float>(M_PI / 4, glm::vec3(0, 1, 0))*glm::scale<float>(glm::vec3(.25, 20, .25)));
	drawCylidner(glm::translate(glm::vec3(-10, 0, 10))*glm::rotate<float>(-M_PI / 2, glm::vec3(1, 0, 0))*glm::rotate<float>(M_PI / 4, glm::vec3(0, 1, 0))*glm::scale<float>(glm::vec3(.25, 20, .25)));
	drawCylidner(glm::translate(glm::vec3(-10, 0, 10))*glm::rotate<float>(-M_PI / 2, glm::vec3(0, 0, 1))*glm::rotate<float>(M_PI / 4, glm::vec3(0, 1, 0))*glm::scale<float>(glm::vec3(.25, 20, .25)));
	m_vao.Bind();
	
	//akadályok
	m_program.SetTexture("texImage", 0, m_texturEarth);
	for (int i = 0; i < 5; i++)
	{
		if (akadalyok[i].active)
			drawAkadaly(glm::translate(glm::vec3(akadalyok[i].x, 0, akadalyok[i].z)));
	}
	


	//golyók
	for (int i = 0; i < balls.size(); i++)
	{
		if (i == 0) {
			m_program.SetUniform("Kd", glm::vec3(1.0, 0.84, 0));
		}
		else {
			m_program.SetUniform("Kd", glm::vec3(0.75, 0.45, 0.125));
		}
		switch (balls[i].m)
		{
		case 1 : 
			m_program.SetTexture("texImage", 0, m_texturEarth);
			break;
		case 2:
			m_program.SetTexture("texImage", 0, m_textureMetal);
			break;
		case 3 :
			m_program.SetTexture("texImage", 0, m_texturScales);
			break;
		default:
			break;
		}
		if (glm::length(balls[i].velocy) == 0)
			int asd = 0;

		if (balls[i].active) {
			drawGolyo(glm::translate(glm::vec3(balls[i].x, balls[i].y, balls[i].z))*(balls[i].status)*balls[i].last_rotate);
			balls[i].last_rotate = balls[i].status;
			
		}
			

		//drawGolyo(glm::translate(glm::vec3(balls[i].x, 1, balls[i].z))*glm::rotate<float>(balls[i].status.z, glm::vec3(1, 0, 0))*glm::rotate<float>(-balls[i].status.x, glm::vec3(0, 0, 1)));
	}
	

	
	// végetért a 3D színtér rajzolása
	m_program.Unuse();

	//
	// UI
	//
	// A következő parancs megnyit egy ImGui tesztablakot és így látszik mit tud az ImGui.
	ImGui::ShowTestWindow();
	// A ImGui::ShowTestWindow implementációja az imgui_demo.cpp-ben található
	// Érdemes még az imgui.h-t böngészni, valamint az imgui.cpp elején a FAQ-ot elolvasni.
	// Rendes dokumentáció nincs, de a fentiek elegendőek kell legyenek.
	
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiSetCond_FirstUseEver);
	// csak akkor lépjünk be, hogy ha az ablak nincs csíkká lekicsinyítve...
	if (ImGui::Begin("Curve designer"))	
	{
		static size_t currentItem = 0;

		ImGui::ListBoxHeader("List", 4);
		for (size_t i = 0; i < m_pointName.size(); ++i)
		{
			if (ImGui::Selectable(m_pointName[i].c_str(), (i==currentItem))  )
				currentItem = i;
		}
		ImGui::ListBoxFooter();

		if (ImGui::Button("Add") && m_pointName.size() < kMaxPointCount)
		{
			m_pointName.push_back("Point " + std::to_string(m_pointName.size()+1));
			m_controlPoints.push_back({ 0,0,0 });
			currentItem = m_pointName.size() - 1;
		}

		ImGui::SameLine();

		if (ImGui::Button("Delete") && m_pointName.size() > 0 && currentItem < m_pointName.size() )
		{
			m_pointName.erase(m_pointName.begin() + currentItem);
			m_controlPoints.erase(m_controlPoints.begin() + currentItem);

			size_t number = currentItem+1;
			for (auto& it = m_pointName.begin()+ currentItem; it != m_pointName.end(); ++it)
			{
				*it = "Point " + std::to_string(number);
				++number;
			}
			if (m_pointName.size() == 0)
				currentItem = 0;
			else
				if (currentItem >= m_pointName.size())
					currentItem = m_pointName.size() - 1;
		}

		if (m_controlPoints.size() > 0)
			ImGui::SliderFloat3("Coordinates", &(m_controlPoints[currentItem][0]), -10, 10);

		ImGui::SliderFloat("Parameter", &m_currentParam, 0, (float)(m_controlPoints.size()-1));

		// 1. feladat: Suzanne feje mindig forduljon a menetirány felé! Először ezt elég síkban (=XZ) megoldani!
		// 2. feladat: valósíts meg egy Animate gombot! Amíg nyomva van az m_currentParameter periodikusan változzon a [0,m_controlPoints.size()-1] intervallumon belül!
		// 3. feladat: egyenközű Catmull-Rom spline-nal valósítsd meg Suzanne görbéjét a mostani törött vonal helyett!

	}
	ImGui::End(); // ...de még ha le is volt, End()-et hívnunk kell

	userEnabled = true;
}

void CMyApp::KeyboardDown(SDL_KeyboardEvent& key)
{
	//m_camera.KeyboardDown(key);
	glm::vec3& atm = m_camera.GetAt()-m_camera.GetEye();
	if (abs(atm.x) > 0) {
		pressedx = true;
	}
	if (abs(atm.z) > 0) {
		pressedz = true;
	}
	if (userEnabled) {
		switch (key.keysym.sym)
		{
		case SDLK_w:
			balls[0].velocy += atm / (float)100;
			if (balls[0].active)
				balls[0].velocy.y = 0;
			break;
		case SDLK_s:
			balls[0].velocy -= atm / (float)100;
			if (balls[0].active)
				balls[0].velocy.y = 0;
			break;
		case SDLK_a:
			atm = glm::vec3(atm.z, 0, -atm.x);
			balls[0].velocy += atm / (float)100;
			if (balls[0].active)
				balls[0].velocy.y = 0;
			break;
		case SDLK_d:
			atm = glm::vec3(atm.z, 0, -atm.x);
			balls[0].velocy -= atm / (float)100;
			if (balls[0].active)
				balls[0].velocy.y = 0;
			break;
		case SDLK_UP:
			atm.y = 0;
			eye = m_camera.GetEye() + glm::normalize(atm);
			atChange += glm::normalize(atm);
			break;
		case SDLK_DOWN:
			atm.y = 0;
			eye = m_camera.GetEye() - glm::normalize(atm);
			atChange -= glm::normalize(atm);
			break;
		case SDLK_LEFT:
			atm = glm::vec3(atm.z, 0, -atm.x);
			eye = m_camera.GetEye() + glm::normalize(atm);
			atChange += glm::normalize(atm);
			break;
		case SDLK_RIGHT:
			atm = glm::vec3(atm.z, 0, -atm.x);
			eye = m_camera.GetEye() - glm::normalize(atm);
			atChange -= glm::normalize(atm);
		default:
			break;
		}
	}
	
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent& key)
{
	//m_camera.KeyboardUp(key);
}

void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse)
{
	m_camera.MouseMove(mouse);
}

void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

// a két paraméterbe az új ablakméret szélessége (_w) és magassága (_h) található
void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h );

	m_camera.Resize(_w, _h);
}

glm::vec3 CMyApp::Eval(float t)
{
	if (m_controlPoints.size() == 0)
		return glm::vec3(0);

	int interval = (int)t;

	if (interval < 0)
		return m_controlPoints[0];
		
	if (interval >= m_controlPoints.size()-1)
		return m_controlPoints[m_controlPoints.size()-1];

	float localT = t - interval;
	return (1- localT)*m_controlPoints[interval] + localT*m_controlPoints[interval+1];
}
