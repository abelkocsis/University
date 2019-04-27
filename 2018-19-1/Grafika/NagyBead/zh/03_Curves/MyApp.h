#pragma once

// C++ includes
#include <memory>

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "ProgramObject.h"
#include "BufferObject.h"
#include "VertexArrayObject.h"
#include "TextureObject.h"

#include "Mesh_OGL3.h"
#include "gCamera.h"

#include <vector>

//Egyéb
#include <stdlib.h>  
#include <time.h> 
#include <stdio.h> 

class CMyApp
{
public:
	CMyApp(void);
	~CMyApp(void);

	bool Init();
	void Clean();

	void Update();
	void Render();

	void KeyboardDown(SDL_KeyboardEvent&);
	void KeyboardUp(SDL_KeyboardEvent&);
	void MouseMove(SDL_MouseMotionEvent&);
	void MouseDown(SDL_MouseButtonEvent&);
	void MouseUp(SDL_MouseButtonEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);
	void Resize(int, int);
protected:
	// görbénk kiértékelése
	glm::vec3 Eval(float);
	float	m_currentParam{ 0 };



	// shaderekhez szükséges változók
	ProgramObject		m_program;		// shaderek programja
	ProgramObject		m_axesProgram;
	ProgramObject		m_pointProgram;

	Texture2D			m_textureMetal;
	Texture2D			m_texturEarth;
	Texture2D			m_texturScales;
	Texture2D			m_texturShell;

	VertexArrayObject	m_vao;			// VAO objektum
	IndexBuffer			m_gpuBufferIndices;		// indexek
	ArrayBuffer			m_gpuBufferPos;	// pozíciók tömbje
	ArrayBuffer			m_gpuBufferNormal;	// normálisok tömbje
	ArrayBuffer			m_gpuBufferTex;	// textúrakoordináták tömbje



	// körlap
	void createDisk();
	VertexArrayObject m_vao_disk;
	ArrayBuffer vbo_disk_pos;
	ArrayBuffer vbo_disk_norm;
	ArrayBuffer vbo_disk_tex;
	//golyo
	void createGolyo();
	VertexArrayObject m_vao_golyo;
	ArrayBuffer vbo_golyo_pos;
	ArrayBuffer vbo_golyo_norm;
	ArrayBuffer vbo_golyo_tex;

	glm::vec3 GetUV(float u, float v);

	// palást
	void createPalast();
	VertexArrayObject m_vao_palast;
	ArrayBuffer vbo_palast_pos;
	ArrayBuffer vbo_palast_norm;
	ArrayBuffer vbo_palast_tex;
	IndexBuffer	palastIndices;		// indexek

	//akadaly
	void createAkadaly();
	VertexArrayObject m_vao_akadaly;
	ArrayBuffer vbo_akadaly_pos;
	ArrayBuffer vbo_akadaly_norm;
	ArrayBuffer vbo_akadaly_tex;
	IndexBuffer	akadalyIndices;


	void drawAkadaly(const glm::mat4& world);
	void drawDisk(const glm::mat4& world);
	void drawCylidner(const glm::mat4& world);
	void drawGolyo(const glm::mat4& world);

	std::unique_ptr<Mesh>	m_mesh;

	gCamera				m_camera;

	const int kMaxPointCount = 10;

	std::vector<glm::vec3>		m_controlPoints{ {-10,0,-10}, {10,0,-10} };
	std::vector<std::string>	m_pointName{ "Point 1", "Point 2" };


	static const int N = 4;
	static const int NG = 20;
	static const int x = 1;
	static const int xh = 2;

	struct ball {
		bool active = true;
		bool zuhan = false;
		float x;
		float z;
		float y = 1;
		glm::vec3 velocy = glm::vec3(0,0,0);
		glm::mat4 status = glm::mat4(1.0f);
		glm::mat4 last_rotate = glm::mat4(1.0f);
		glm::vec3 axis = glm::vec3(1,1,1);
		int m = 1;
		bool uj = false;
		float lastMove;
		bool sullyedes = false;
	};

	struct hole {
		float x;
		float z;
	};

	std::vector<ball> balls;

	struct Vertex
	{
		glm::vec3 p;
		glm::vec3 c;
	};

	struct akadaly {
		int x;
		int z;
		bool active = false;
		int utkozes = 0;
	};

	akadaly akadalyok[5];

	void newBalls();
	void falUtkozes(int i);
	bool utkozes(int i, int j);
	void golyoUtkozes(int i);
	void akadalyUtkozes(int i);
	void inHole(int i);
	void akadalyHappen();

	Uint32 last_akadaly;


	glm::vec3 eye = glm::vec3(0, 10, 0);
	glm::vec3 atChange = glm::vec3(0,0,0);
	glm::vec3 up = glm::vec3(0, 1, 0);;

	bool userEnabled = false;
	int startTime;
	int currentTime;
	Uint32 last_time_3;
	Uint32 last_time_2;
	bool pressedx = false;
	bool pressedz = false;
	bool canIDie = true;
	float g = 10;
	float d = 0.00001;
	float seged = 0.2;
};

