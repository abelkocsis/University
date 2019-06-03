#include "GameView.h"

#include <math.h>
#include <vector>

#include <array>
#include <list>
#include <tuple>

#include "imgui\imgui.h"

#include "ObjParser_OGL3.h"

GameView::GameView(void)
{
	playingMusic = false;
	buildMode = false;
	mouseX = 0;
	mouseY = 0;
	chosen = -1;
	lastKey = 0;
	gameover = false;
	menu = true;
	menu_settings = false;
	exited = false;
	pause = false;
	manager = new GameModel;
}

GameView::~GameView(void)
{
	delete manager;
}

bool GameView::Base_Init()
{
	Base.shader.Init({
		{ GL_VERTEX_SHADER, "myVert.vert"},
		{ GL_FRAGMENT_SHADER, "myFrag.frag"}
		},
	{
		{ 0, "vs_in_pos" },					
		{ 1, "vs_in_normal" },				
		{ 2, "vs_out_tex0" },				
	});
	Base.shader.LinkProgram();

	Base.fragments = 3;
	Base.texels.resize(Base.fragments);
	Base.meshes.resize(Base.fragments);

	Base.texels[0].FromFile("Objects/baseA.jpg");
	Base.texels[1].FromFile("Objects/baseB.jpg");
	Base.texels[2].FromFile("Objects/baseC.jpg");
	//Base.texels[3].FromFile("baseD.jpg");

	Base.meshes[0] = ObjParser::parse("Objects/baseA.obj");
	Base.meshes[1] = ObjParser::parse("Objects/baseB.obj");
	Base.meshes[2] = ObjParser::parse("Objects/baseC.obj");
	//Base.meshes[3] = ObjParser::parse("baseD.obj");

	return true;
}

bool GameView::Barrack_Init()
{
	Barrack.shader.Init({
		{ GL_VERTEX_SHADER, "myVert.vert"},
		{ GL_FRAGMENT_SHADER, "myFrag.frag"}
		},
	{
		{ 0, "vs_in_pos" },					
		{ 1, "vs_in_normal" },				
		{ 2, "vs_out_tex0" },				
	});
	Barrack.shader.LinkProgram();

	Barrack.BaseTransformation = glm::scale(glm::vec3(0.35f, 0.35f, 0.35f));

	Barrack.fragments = 1;
	Barrack.texels.resize(Barrack.fragments);
	Barrack.meshes.resize(Barrack.fragments);
	
	Barrack.texels[0].FromFile("Objects/barrack.jpg");

	Barrack.meshes[0] = ObjParser::parse("Objects/barrack.obj");
	
	return true;
}

bool GameView::Field_Init()
{
	Field.shader.Init({
		{ GL_VERTEX_SHADER, "Field.vert"},
		{ GL_FRAGMENT_SHADER, "Field.frag"}
		},
	{
		{ 0, "vs_in_pos" },				
		{ 1, "vs_in_normal" },				
		{ 2, "vs_out_tex0" },				
	});
	Field.shader.LinkProgram();

	Field.BaseTransformation = glm::rotate(float(M_PI / 2.0f), glm::vec3(0, 1, 0)) * 
							   glm::scale(glm::vec3(0.555f, 0.1f, 0.95f)) * 
							   glm::rotate( float(M_PI / 2.0f), glm::vec3(-1,0,0) ) ;

	Field.fragments = 1;
	Field.texels.resize(Field.fragments);
	Field.meshes.resize(Field.fragments);

	Field.texels[0].FromFile("Objects/field.jpg");

	Field.meshes[0] = ObjParser::parse("Objects/field.obj");

	return true;
}

bool GameView::Tower_Init()
{
	Tower.shader.Init({
		{ GL_VERTEX_SHADER, "myVert.vert"},
		{ GL_FRAGMENT_SHADER, "myFrag.frag"}
		},
	{
		{ 0, "vs_in_pos" },				
		{ 1, "vs_in_normal" },			
		{ 2, "vs_out_tex0" },				
	});
	Tower.shader.LinkProgram();

	Tower.BaseTransformation = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));

	Tower.fragments = 1;
	Tower.texels.resize(Tower.fragments);
	Tower.meshes.resize(Tower.fragments);

	Tower.texels[0].FromFile("Objects/tower.jpg");

	Tower.meshes[0] = ObjParser::parse("Objects/tower.obj");

	return true;
}

bool GameView::SmallTower_Init()
{
	SmallTower.shader.Init({
		{ GL_VERTEX_SHADER, "myVert.vert"},
		{ GL_FRAGMENT_SHADER, "myFrag.frag"}
		},
	{
		{ 0, "vs_in_pos" },
		{ 1, "vs_in_normal" },
		{ 2, "vs_out_tex0" },
	});
	SmallTower.shader.LinkProgram();

	SmallTower.BaseTransformation = glm::scale(glm::vec3(0.035f, 0.035f, 0.035f));

	SmallTower.fragments = 1;
	SmallTower.texels.resize(SmallTower.fragments);
	SmallTower.meshes.resize(SmallTower.fragments);

	SmallTower.texels[0].FromFile("Objects/smalltower.jpg");

	SmallTower.meshes[0] = ObjParser::parse("Objects/smalltower.obj");

	return true;
}

bool GameView::DefaultTower_Init()
{
	DefaultTower.shader.Init({
		{ GL_VERTEX_SHADER, "myVert.vert"},
		{ GL_FRAGMENT_SHADER, "myFrag.frag"}
		},
	{
		{ 0, "vs_in_pos" },
		{ 1, "vs_in_normal" },
		{ 2, "vs_out_tex0" },
	});
	DefaultTower.shader.LinkProgram();

	DefaultTower.BaseTransformation = glm::scale(glm::vec3(3.1f, 3.1f, 3.1f));

	DefaultTower.fragments = 1;
	DefaultTower.texels.resize(DefaultTower.fragments);
	DefaultTower.meshes.resize(DefaultTower.fragments);

	DefaultTower.texels[0].FromFile("Objects/DefaultTower.jpeg");

	DefaultTower.meshes[0] = ObjParser::parse("Objects/DefaultTower.obj");

	return true;
}

bool GameView::Knight_Init()
{
	Knight.shader.Init({
		{ GL_VERTEX_SHADER, "myVert.vert"},
		{ GL_FRAGMENT_SHADER, "myFrag.frag"}
		},
	{
		{ 0, "vs_in_pos" },
		{ 1, "vs_in_normal" },
		{ 2, "vs_out_tex0" },
	});
	Knight.shader.LinkProgram();

	Knight.BaseTransformation = glm::scale(glm::vec3(4.0f, 4.0f, 4.0f));

	Knight.fragments = 1;
	Knight.texels.resize(Knight.fragments);
	Knight.meshes.resize(Knight.fragments);

	Knight.texels[0].FromFile("Objects/chevalier.jpg");

	Knight.meshes[0] = ObjParser::parse("Objects/chevalier.obj");

	return true;
}

bool GameView::Cube_Init()
{
	Cube.shader.Init({
		{ GL_VERTEX_SHADER, "Button.vert"},
		{ GL_FRAGMENT_SHADER, "Button.frag"}
		},
	{
		{ 0, "vs_in_pos" },
		{ 1, "vs_in_normal" },
		{ 2, "vs_out_tex0" },
	});
	Cube.shader.LinkProgram();

	Cube.BaseTransformation = glm::scale(glm::vec3(3.0f, 3.0f, 0.01f));

	Cube.fragments = 12; //NewGame , Settings, Exit, GameOver, MainMenu, normalsold, tanksold, strongsold, startserver,connect, win, lose
	Cube.texels.resize(Cube.fragments);
	Cube.meshes.resize(Cube.fragments);

	Cube.texels[0].FromFile("Objects/Resume.jpg");
	Cube.texels[1].FromFile("Objects/Settings.jpg");
	Cube.texels[2].FromFile("Objects/Exit.jpg");
	Cube.texels[3].FromFile("Objects/GameOver.jpg");
	Cube.texels[4].FromFile("Objects/Menu.jpg");
	Cube.texels[5].FromFile("Objects/NormalSoldier.jpg");
	Cube.texels[6].FromFile("Objects/TankSoldier.jpg");
	Cube.texels[7].FromFile("Objects/StrongSoldier.jpg");
	Cube.texels[8].FromFile("Objects/StartServer.jpg");
	Cube.texels[9].FromFile("Objects/Connect.jpg");
	Cube.texels[10].FromFile("Objects/Win.jpg");
	Cube.texels[11].FromFile("Objects/Lose.jpg");

	for(int i = 0; i < Cube.fragments; ++i)
		Cube.meshes[i] = ObjParser::parse("Objects/cube.obj");

	return true;
}

bool GameView::Square_Init() {
	Square_Shader.Init({
		{ GL_VERTEX_SHADER, "Square.vert"},
		{ GL_FRAGMENT_SHADER, "Square.frag"}
		}, {
			{ 0, "vs_in_pos" },
		}
		);
	Square_Shader.LinkProgram();
	return true;
}

bool GameView::Init()
{
	glClearColor(0.5,0.5,0.5, 1);

	glDisable(GL_CULL_FACE); //hátlapeldobás kikapcsolása
	glEnable(GL_DEPTH_TEST); //mélységi takarás

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_camera.SetProj(45.0f, 640.0f / 480.0f, 0.01f, 1000.0f);

	bool inits = true &&
		Tower_Init() &&
		Barrack_Init() &&
		Field_Init() &&
		SmallTower_Init() &&
		DefaultTower_Init() &&
		Knight_Init() &&
		Square_Init() &&
		Cube_Init();

	return inits;
}

void GameView::newGame(int isServer)
{
	if (strlen(ip) > 6 && strlen(port) > 0)
	{
		menu = false;
		playingMusic = false;
		buildMode = false;
		mouseX = 0;
		mouseY = 0;
		chosen = -1;
		lastKey = 0;
		gameover = false;
		pause = false;
		manager->init(isServer, ip, port);
		menu_settings = false;
		if (isServer == 1) server = true;
		if (isServer == 0) server = false;
	}
}

void GameView::Clean()
{
}

void GameView::Update()
{
	static Uint32 last_time = SDL_GetTicks();
	float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;

	m_camera.Update(delta_time);

	last_time = SDL_GetTicks();

	gameover = manager->isGameOver();

	if (!menu) {
		if (server) 
			you = p2, enemy = p1;
		else 
			you = p1, enemy = p2;

		if (!gameover) {
			myTurn = !(server && manager->getCurrentPlayer() == p1 || !server && manager->getCurrentPlayer() == p2);
			if (!myTurn) manager->checkAnswer();
		}
	}
}


void GameView::Base_Render(Coordinate c, glm::vec4 Ka) {
	//glm::vec4 Ka = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	glm::vec4 Kd = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	glm::vec4 Ks = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	Object_Render(Barrack, glm::translate(glm::vec3(c.col * squareSize - ((columns - 1) * squareSize / 2.0f), 2,
		c.row * squareSize - ((rows - 1) * squareSize / 2.0f))),
		Ka, Kd, Ks
	);
}

void GameView::Tower_Render(Coordinate c, glm::vec4 Ka) {
	//glm::vec4 Ka = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	glm::vec4 Kd = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	glm::vec4 Ks = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	Object_Render(Tower, glm::translate(glm::vec3(c.col * squareSize - ((columns - 1) * squareSize / 2.0f), 2, 
												  c.row * squareSize - ((rows - 1) * squareSize / 2.0f))),
		Ka, Kd, Ks
	);
}

void GameView::SmallTower_Render(Coordinate c, glm::vec4 Ka) {
	//glm::vec4 Ka = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	glm::vec4 Kd = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	glm::vec4 Ks = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	Object_Render(SmallTower, glm::translate(glm::vec3(c.col * squareSize - ((columns - 1) * squareSize / 2.0f), 2,
		c.row * squareSize - ((rows - 1) * squareSize / 2.0f))), 
		Ka, Kd, Ks
	);
}

void GameView::DefaultTower_Render(Coordinate c, glm::vec4 Ka) {
	//glm::vec4 Ka = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	glm::vec4 Kd = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	glm::vec4 Ks = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	Object_Render(DefaultTower, glm::translate(glm::vec3(c.col * squareSize - ((columns - 1) * squareSize / 2.0f), 2,
		c.row * squareSize - ((rows - 1) * squareSize / 2.0f))), 
		Ka, Kd, Ks
	);
}

void GameView::Knight_Render(Coordinate c, glm::mat4 transform, glm::vec4 Ka ) {
	//glm::vec4 Ka = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	glm::vec4 Kd = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	glm::vec4 Ks = glm::vec4(0.5f, 0.5f, 0.5f, 0);
	Object_Render(Knight, glm::translate(glm::vec3(c.col * squareSize - ((columns - 1) * squareSize / 2.0f), 2,
		c.row * squareSize - ((rows - 1) * squareSize / 2.0f))) * transform,
		Ka,
		Kd,
		Ks
	);
}

void GameView::Field_Render() {
	glm::mat4 WORLD = glm::mat4(1.0f) * Field.BaseTransformation;

	Field.shader.Use();
	Field.shader.SetUniform("meshID", meshIDs);
	Field.shader.SetUniform("world", WORLD);
	Field.shader.SetUniform("worldIT", glm::transpose(glm::inverse(WORLD)));
	Field.shader.SetUniform("MVP", m_camera.GetViewProj() * WORLD);

	Field.shader.SetTexture("texImage", 0, Field.texels[0]);
	Field.meshes[0]->draw();

	meshIDs++;
	Field.shader.Unuse();
} //TODO  : draw turrets range with a colored circle

void GameView::Square_Render(glm::mat4 World, Coordinate c, float red, float green) {
	Square_Shader.Use();
	Square_Shader.SetUniform("world", World);
	Square_Shader.SetUniform("worldIT", glm::transpose(glm::inverse(World)));
	Square_Shader.SetUniform("MVP", m_camera.GetViewProj() * World);
	Square_Shader.SetUniform("I", c.row);
	Square_Shader.SetUniform("J", c.col);
	Square_Shader.SetUniform("red", red);
	Square_Shader.SetUniform("green", green);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	Square_Shader.Unuse();
}

void GameView::Button_Render(int offsetY, int offsetX, int type, float sizeX, float sizeY, bool pushable)
{
	float oy = offsetY * 5.0f;
	float ox = offsetX * 5.0f;
	float dist = m_camera.GetCameraDistance();
	float theta = m_camera.GetElevationAngle();
	float fi = m_camera.GetRotationAngle();
	float xx = dist * cosf(fi + M_PI) * sinf(M_PI / 2.0f - theta);
	float zz = dist * sinf(fi + M_PI) * sinf(M_PI / 2.0f - theta);
	float yy = dist * cosf(M_PI / 2.0f - theta);
	float x = dist * cosf(fi - M_PI / 2.0f) * sinf(theta);
	float z = dist * sinf(fi - M_PI / 2.0f) * sinf(theta);
	glm::vec3 camPos = glm::normalize(m_camera.GetEye());
	glm::vec3 camPosNormX = normalize(glm::vec3(x, 0, z));
	glm::vec3 camPosNormY = normalize(glm::vec3(xx,yy,zz));
	glm::mat4 chosenButton = glm::mat4(1.0f);

	if (chosen == type && pushable)
		chosenButton = glm::scale(glm::vec3(sizeX * 1.2f, sizeY * 1.2f, 0.01f));
	else
		chosenButton = glm::scale(glm::vec3(sizeX, sizeY, 0.01f));

	glm::mat4 WORLD = glm::translate(camPosNormX * ox) * glm::translate(camPosNormY * oy) * glm::translate(camPos * (dist - 50.0f) ) * glm::rotate(  -fi - float(M_PI / 2.0f), glm::vec3(0,1,0) ) * glm::rotate(float(M_PI / 2.0f ) - theta, glm::vec3(1,0,0)) * chosenButton * Cube.BaseTransformation;
	Cube.shader.Use();
	Cube.shader.SetUniform("meshID", type + 100);
	Cube.shader.SetUniform("world", WORLD);
	Cube.shader.SetUniform("worldIT", glm::transpose(glm::inverse(WORLD)));
	Cube.shader.SetUniform("MVP", m_camera.GetViewProj() * WORLD);

	Cube.shader.SetTexture("texImage", 0, Cube.texels[type]);
	Cube.meshes[type]->draw();

	Cube.shader.Unuse();
}

void GameView::Object_Render(Object& Obj, glm::mat4 World, glm::vec4 Ka, glm::vec4 Kd, glm::vec4 Ks) {
	glm::mat4 WORLD = World * Obj.BaseTransformation;

	Obj.shader.Use();
	Obj.shader.SetUniform("eye_pos", m_camera.GetEye());
	Obj.shader.SetUniform("meshID", meshIDs);
	Obj.shader.SetUniform("world", WORLD);
	Obj.shader.SetUniform("worldIT", glm::transpose(glm::inverse(WORLD)));
	Obj.shader.SetUniform("MVP", m_camera.GetViewProj() * WORLD);

	Obj.shader.SetUniform("Ka", Ka);
	Obj.shader.SetUniform("Kd", Kd);
	Obj.shader.SetUniform("Ks", Ks);

	for (int i = 0; i < Obj.fragments; ++i)
	{
		Obj.shader.SetTexture("texImage", 0, Obj.texels[i]);
		Obj.meshes[i]->draw();
	}
	
	meshIDs++;
	Obj.shader.Unuse();
}

void GameView::RenderMatrix(const std::vector< std::vector<::Field> >& Map)
{
	glDisable(GL_BLEND);
	if (CheckIndex(MatrixCursor) && Map[MatrixCursor.col][MatrixCursor.row].Status != Buildable) MatrixCursor = Coordinate(-1, -1);
	for (int i = 0; i < columns; ++i)
		for (int j = 0; j < rows; ++j)
		{
			float k = 4.8f, red, green;
			if (MatrixCursor.row == i && MatrixCursor.col == j) k = 5.5f;
			glm::mat4 rotMat;

			if (Map[j][i].Status == Buildable) { red = 0.0f ; green = 1.0f; }
			if (Map[j][i].Status == Occupied) { red = 1.0f; green = 0.0f; }
			if (Map[j][i].Status == Sol) { red = 1.0f; green = 0.0f; }
			if (Map[j][i].Status == Free) { red = 0.7f; green = 0.6f; }
			if (Map[j][i].Status == Unobtainable) { red = 1.0f; green = 0.0f; }

			Square_Render(
				glm::translate(glm::vec3(i * squareSize - ( (columns-1) * squareSize / 2.0f), 2, j * squareSize - ( (rows-1) * squareSize / 2.0f))) 
				* glm::scale(glm::vec3(k, k, k)), 
				Coordinate(i,j), 
				red, 
				green
			);
		}
	glEnable(GL_BLEND);
}

void GameView::Before_Render(const std::vector< std::vector<::Field> >& Map)
{
	meshIDs = 1;
	if(manager->getCurrentPlayer() == p1) glClearColor(1, 0.1, 0.1, 1);
	else glClearColor(0.1, 0.1, 1, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderMatrix(Map);
	RenderButtons();
	glReadBuffer(GL_BACK);
	glReadPixels(mouseX, windowY - mouseY - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pix);
	chosen = int(pix[3]) - 100;
	MatrixCursor.row = int(pix[2]);
	MatrixCursor.col = int(pix[3]);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameView::Draw()
{
	if (menu_settings) Settings_Render();
	else {
		if (menu) Menu_Render();
		else Render();
	}
}

void GameView::settingsGui()
{
	ImGui::Begin("Inputtext test");

	ImGui::InputText("IP address", ip, sizeof(ip));

	ImGui::InputText("Port", port, sizeof(port));

	ImGui::End();
}

void GameView::Menu_Render()
{
	Update();
	glClearColor(0.1f, 0.52f, 0.7f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glDisable(GL_BLEND);
	Button_Render(3, 0, 8);
	Button_Render(1, 0, 9);
	Button_Render(-1, 0, 1);
	Button_Render(-3, 0, 2);
	glEnable(GL_BLEND);

	glReadBuffer(GL_BACK);
	glReadPixels(mouseX, windowY - mouseY - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pix);
	chosen = int(pix[3]) - 100;
}

void GameView::Settings_Render()
{
	Update();
	glClearColor(0.1f, 0.52f, 0.7f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_BLEND);
	Button_Render(-2, 0, 4);
	glEnable(GL_BLEND);

	glReadBuffer(GL_BACK);
	glReadPixels(mouseX, windowY - mouseY - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pix);
	chosen = int(pix[3]) - 100;

	settingsGui();
}

void GameView::RenderButtons()
{
	glDisable(GL_BLEND);
	if (!menu && gameover) {
		int t = 3;
		if (manager->getCastleHp(you) < 1)
			t = 11;
		else
			t = 10;
		Button_Render(3, 0, t, 4.86f, 1.8f, false);
		//Button_Render(0, 0, 0);
		Button_Render(-2, 0, 2);
	}
	if (!menu && !gameover && pause) {
		Button_Render(0, 0, 0);
		Button_Render(-2, 0, 2);
	}
	if (!menu && !gameover && !pause && false) {
		Button_Render(5, -5, 5, 0.7f, 0.7f, true);
		Button_Render(5, -4, 6, 0.7f, 0.7f, true);
		Button_Render(5, -3, 7, 0.7f, 0.7f, true);
		Button_Render(5, 3, 5, 0.7f, 0.7f, true);
		Button_Render(5, 4, 6, 0.7f, 0.7f, true);
		Button_Render(5, 5, 7, 0.7f, 0.7f, true);
	}
	glEnable(GL_BLEND);
}

void GameView::Render()
{
	std::vector<std::vector<::Field> > Map = manager->getMap();
	glm::vec4 Ka;
	W currentPlayer = manager->getCurrentPlayer();

	Update();
	Before_Render(Map);
	Field_Render();

	for(int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
		{
			glm::mat4 rotMat = glm::rotate(float(M_PI / 2.0f), glm::vec3(0, 1, 0));
			if (Map[i][j].Whose == W::p1) { rotMat = glm::rotate(float(M_PI / 2.0f), glm::vec3(0, 1, 0)); Ka = glm::vec4(1.0f, 0.4f, 0.4f, 0.0f); }
			if (Map[i][j].Whose == W::p2) { rotMat = glm::rotate(float(-M_PI / 2.0f), glm::vec3(0, 1, 0)); Ka = glm::vec4(0.4f, 0.4f, 1.0f, 0.0f); }
			if (Map[i][j].Whose == W::nobody) { rotMat = glm::mat4(1.0f); Ka = glm::vec4(0.5f, 0.5f, 0.5f, 0.0f);}

			if( (Map[i][j].Obj == Tower1 || Map[i][j].Obj == Tower2 || Map[i][j].Obj == Tower3 || Map[i][j].Obj == Castle1 || Map[i][j].Obj == Castle2) 
			    && Map[i][j].Whose == currentPlayer)

				for(int k = i - build_range; k <= i + build_range; ++k)
					for (int l = j - build_range; l <= j + build_range; ++l) {
						if (CheckIndex(Coordinate(l, k)) && abs(i - k) + abs(j - l) <= build_range && Map[k][l].Status == Free)
							Map[k][l].Status = Buildable;
					}

			switch (Map[i][j].Obj) {
				case Empty:
					break;
				case Tower1:
					DefaultTower_Render(Coordinate(i, j), Ka);
					break;
				case Tower2:
					SmallTower_Render(Coordinate(i, j), Ka);
					break;
				case Tower3:
					Tower_Render(Coordinate(i, j), Ka);
					break;
				case Soldier1:
					Knight_Render(Coordinate(i, j), glm::scale(glm::vec3(0.8f, 0.8f, 0.8f))*rotMat , Ka );
					break;
				case Soldier2:
					Knight_Render(Coordinate(i, j), glm::scale(glm::vec3(1.1f, 1.1f, 1.1f))*rotMat, Ka );
					break;
				case Soldier3:
					Knight_Render(Coordinate(i, j), glm::scale(glm::vec3(1.4f, 1.4f, 1.4f))*rotMat, Ka );
					break;
				case Castle1:
					Base_Render(Coordinate(i, j), Ka);
					break;
				case Castle2:
					Base_Render(Coordinate(i, j), Ka); // TODO rotate 180 degrees
					break;
				default:
					break;
			}
		}

	RenderButtons();
	renderGui();
	if(buildMode) RenderMatrix(Map);
}

void GameView::renderGui()
{
	ImGui::SetNextWindowPos(ImVec2(200, 800), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("GUI"))
	{
		W you, enemy;
		if(server) you = p2, enemy = p1;
		else you = p1, enemy = p2;

		ImGui::Text("MY MONEY:  ");
		int m1 = manager->getMoney(you);
		std::string s = std::to_string(m1);
		char const *pc = s.c_str();
		ImGui::SameLine();
		ImGui::Text(pc);

		ImGui::Text("MY CASTLE:  ");
		int c1 = (manager->getCastleHp(you));
		s = std::to_string(c1);
		char const *cc = s.c_str();
		ImGui::SameLine();
		ImGui::Text(cc);

		ImGui::Text("ENEMY MONEY:  ");
		int m2 = manager->getMoney(enemy);
		s = std::to_string(m2);
		const char *pc2 = s.c_str();
		ImGui::SameLine();
		ImGui::Text(pc2);

		ImGui::Text("ENEMY CASTLE:  ");
		int c2 = (manager->getCastleHp(enemy));
		s = std::to_string(c2);
		char const *cc2 = s.c_str();
		ImGui::SameLine();
		ImGui::Text(cc2);

		if (!gameover && myTurn) {

			if (ImGui::Button("Pass")) {
				manager->round(0, Coordinate(-1, -1));
				if (buildMode) buildMode = false;
			}

			std::string s = std::string("Base tower - ") + std::to_string(tower1_cost);
			char const *p = s.c_str();
			if (ImGui::Button(p) && m1 >= tower1_cost) {
				if (lastKey == 1) lastKey = 0, buildMode = false;
				else		 lastKey = 1, buildMode = true;
			}
			
			s = std::string("Longrange tower - ") + std::to_string(tower2_cost);
			p = s.c_str();
			if (ImGui::Button(p) && m1 >= tower2_cost) {
				if (lastKey == 2) lastKey = 0, buildMode = false;
				else		 lastKey = 2, buildMode = true;
			}

			s = std::string("Powerful tower - ") + std::to_string(tower3_cost);
			p = s.c_str();
			if (ImGui::Button(p) && m1 >= tower3_cost) {
				if (lastKey == 3) lastKey = 0, buildMode = false;
				else		 lastKey = 3, buildMode = true;
			}

			s = std::string("Normal soldier - ") + std::to_string(sol1_cost);
			p = s.c_str();
			if (ImGui::Button(p) && m1 >= sol1_cost) {
				manager->round(4, Coordinate(-1, -1));
				if (buildMode) buildMode = false;
			}

			s = std::string("Tank soldier - ") + std::to_string(sol2_cost);
			p = s.c_str();
			if (ImGui::Button(p) && m1 >= sol2_cost) {
				manager->round(5, Coordinate(-1, -1));
				if (buildMode) buildMode = false;
			}

			s = std::string("Epic soldier - ") + std::to_string(sol3_cost);
			p = s.c_str();
			if (ImGui::Button(p) && m1 >= sol3_cost) {
				manager->round(6, Coordinate(-1, -1));
				if (buildMode) buildMode = false;
			}
		}
		//ImGui::SliderFloat("thats a slider mah boii", &squareSize, 0, 11);
	}
	ImGui::End();
}
/*
0 - pass
1,2,3 - build tower 1,2,3
4,5,6 - train soldier 1,2,3
*/
void GameView::KeyboardDown(SDL_KeyboardEvent& key)
{
	W currentPlayer = manager->getCurrentPlayer();
	m_camera.KeyboardDown(key);
	if (!gameover && !menu) {
		if (!pause)
			switch (key.keysym.sym) {
			case SDLK_ESCAPE:
				pause = true;
				break;
			case SDLK_m:
				playMusic("music/highlands.wav", SDL_MIX_MAXVOLUME / 5), playingMusic = true;
				break;
			case SDLK_p:
				if (playingMusic) {
					playingMusic = false;
					pauseAudio();
				}
				else {
					playingMusic = true;
					unpauseAudio();
				}
				break;
			/*
			case SDLK_0:
				manager->round(0, Coordinate(-1, -1));
				break;
			case SDLK_1:
				if (lastKey == 1) lastKey = 0, buildMode = false;
				else		 lastKey = 1, buildMode = true;
				break;
			case SDLK_2:
				if (lastKey == 2) lastKey = 0, buildMode = false;
				else		 lastKey = 2, buildMode = true;
				break;
			case SDLK_3:
				if (lastKey == 3) lastKey = 0, buildMode = false;
				else		 lastKey = 3, buildMode = true;
				break;
			case SDLK_4:
				manager->round(4, Coordinate(7, 2));
				break;
			case SDLK_5:
				manager->round(5, Coordinate(7, 2));
				break;
			case SDLK_6:
				manager->round(6, Coordinate(7, 2));
				break;
			case SDLK_b:
				buildMode = !buildMode;
				break;
			*/
			}
		else
			switch (key.keysym.sym) {
			case SDLK_ESCAPE:
				pause = !pause;
				break;
			}
	}
}

void GameView::KeyboardUp(SDL_KeyboardEvent& key)
{
	m_camera.KeyboardUp(key);
}

void GameView::MouseMove(SDL_MouseMotionEvent& mouse)
{
	//m_camera.MouseMove(mouse);
	mouseX = mouse.x;
	mouseY = mouse.y;
}

void GameView::MouseDown(SDL_MouseButtonEvent& mouse)
{
	Coordinate MC = Coordinate(MatrixCursor.col, MatrixCursor.row);
	if (!menu && CheckIndex(MatrixCursor))
		switch (lastKey) {
		case 1:
			if (manager->round(1, MC)) {
				std::cout << "\nround(1) called with" << MC.row << " row, " << MC.col << " col\n";
				lastKey = 0;
				buildMode = false;
			}
			break;
		case 2:
			if (manager->round(2, MC)) {
				std::cout << "\nround(2) called with" << MC.row << " row, " << MC.col << " col\n";
				lastKey = 0;
				buildMode = false;
			}
			break;
		case 3:
			if (manager->round(3, MC)) {
				std::cout << "\nround(3) called with" << MC.row << " row, " << MC.col << " col\n";
				lastKey = 0;
				buildMode = false;
			}
			break;
		}
	if (menu)
	{
		switch (chosen) {
		case 8:
			newGame(1);
			break;
		case 9:
			newGame(0);
			break;
		case 1:
			menu_settings = true;
			break;
		case 2:
			exited = true;
			break;
		case 4:
			menu_settings = false;
			break;
		}
	}
	if (!menu && (pause) || gameover)
	{
		switch (chosen) {
		case 0:
			pause = false;
			break;
		case 2:
			manager->disconnect();
			exited = true;
			break;
		}
	}
}

void GameView::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void GameView::MouseWheel(SDL_MouseWheelEvent& wheel)
{
	m_camera.MouseWheel(wheel);
}

void GameView::Resize(int _w, int _h)
{
	windowX = _w;
	windowY = _h;

	glViewport(0, 0, _w, _h );
	
	m_camera.Resize(_w, _h);
}