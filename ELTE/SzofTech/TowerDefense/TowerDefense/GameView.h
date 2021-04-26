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
#include "audio.h"
#include "GameModel.h"

#include <vector>

struct Object {
	int fragments;
	glm::mat4 BaseTransformation = glm::mat4(1.0f);

	ProgramObject shader;
	std::vector<Texture2D> texels;
	std::vector< std::unique_ptr<Mesh> > meshes;
};

class GameView
{
public:
	GameView(void);
	~GameView(void);

	bool Init();
	bool checkGame() { return gameover; }
	bool exitGame() { return exited; }

	void Clean();
	void Update();
	void Draw();
	void Menu_Render();
	void Settings_Render();
	void Render();
	void RenderButtons();

	void Base_Render(Coordinate c, glm::vec4 Ka);
	void Tower_Render(Coordinate c, glm::vec4 Ka);
	void Field_Render();
	void SmallTower_Render(Coordinate c, glm::vec4 Ka);
	void DefaultTower_Render(Coordinate c, glm::vec4 Ka);
	void Knight_Render(Coordinate c, glm::mat4 transform, glm::vec4 Ka);
	void Button_Render(int offsetY, int offsetX, int type, float sizeX = 2.7f, float sizeY = 1.0f, bool pushable = true);

	void Before_Render(const std::vector< std::vector<Field> >& Map);
	void RenderMatrix(const std::vector< std::vector<Field> >& Map);

	void KeyboardDown(SDL_KeyboardEvent&);
	void KeyboardUp(SDL_KeyboardEvent&);
	void MouseMove(SDL_MouseMotionEvent&);
	void MouseDown(SDL_MouseButtonEvent&);
	void MouseUp(SDL_MouseButtonEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);
	void Resize(int, int);

	int getRows() { return rows; }
	int getColumns() { return columns; }

	Coordinate getCursor() { return MatrixCursor; }

protected:
	GameModel* manager;

	bool Base_Init();
	bool Barrack_Init();
	bool Knight_Init();
	bool Tower_Init();
	bool SmallTower_Init();
	bool DefaultTower_Init();
	bool Field_Init();
	bool Square_Init();
	bool Cube_Init();
	void newGame(int isServer);

	void Object_Render(Object& obj, glm::mat4 World, 
					   glm::vec4 Ka = glm::vec4(0.5f, 0.5f, 0.5f, 0),
		               glm::vec4 Kd = glm::vec4(0.5f, 0.5f, 0.5f, 0),
		               glm::vec4 Ks = glm::vec4(0.5f, 0.5f, 0.5f, 0));
	void Square_Render(glm::mat4 World, Coordinate c, float red = 0.0f, float green = 1.0f);
	bool CheckIndex(Coordinate x) { return (x.row >= 0 && x.row < columns && x.col >= 0 && x.col < rows);	}
	void renderGui();
	void settingsGui();

	bool				playingMusic, gameover, buildMode, menu, exited, pause, menu_settings, server, myTurn;
	int					meshIDs, chosen;
	int					mouseX, mouseY;
	int					lastKey;
	int					windowX, windowY;
	Coordinate			MatrixCursor;
	int					rows = 15, columns = 25;
	float				squareSize = 11.0f;
	char				ip[16], port[6];

	Object				Base;
	Object				Barrack;
	Object				Tower;
	Object				Field;
	Object				SmallTower;
	Object				SmallBarrack;
	Object				Knight;
	Object				DefaultTower;
	Object				Cube;

	gCamera				m_camera;

	GLubyte				pix[4];

	W					you, enemy;

	ProgramObject		Square_Shader;
};

/*

// Initialize Simple-SDL2-Audio on default audio device
void initAudio(void);

// Play many Sounds or single Musics
void playSound(const char * filename, int volume);
void playMusic(const char * filename, int volume);

// Clean up Simple-SDL2-Audio
void endAudio(void);

// Pause or Unpause running audio
void pauseAudio(void);
void unpauseAudio(void);

// Advanced functions used for caching WAV files in memory, create, play many times, free
Audio * createAudio(const char * filename, uint8_t loop, int volume);
void playSoundFromMemory(Audio * audio, int volume);
void playMusicFromMemory(Audio * audio, int volume);
void freeAudio(Audio * audio);

*/

