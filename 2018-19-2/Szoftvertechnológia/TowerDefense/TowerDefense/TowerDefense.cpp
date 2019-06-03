// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_opengl.h>

// standard
#include <iostream>
#include <sstream>

// imgui
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl_gl3.h"

#include "GameView.h"
#include "audio.h"
#include "GameModel.h"

void exitProgram()
{
	SDL_Quit();

	std::cout << "Kil�p�shez nyomj meg egy billenty�t..." << std::endl;
	std::cin.get();
}

int main(int argc, char* args[])
{
	atexit(exitProgram);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
	{
		// irjuk ki a hibat es terminaljon a program
		std::cout << "[SDL ind�t�sa]Hiba az SDL inicializ�l�sa k�zben: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// �ll�tsuk be, hogy h�ny biten szeretn�nk t�rolni a piros, z�ld, k�k �s �tl�tszatlans�gi inform�ci�kat pixelenk�nt
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// duplapufferel�s
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// m�lys�gi puffer h�ny bites legyen
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// antialiasing - ha kell - n�zz�k meg, hogy mi lesz a pont-primit�vekb�l, hogy ha bekapcsoljuk!
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

	// hozzuk l�tre az ablakunkat
	SDL_Window *win = 0;
	win = SDL_CreateWindow("Hello SDL&OpenGL!",		// az ablak fejl�ce
		0,						// az ablak bal-fels� sark�nak kezdeti X koordin�t�ja
		0,						// az ablak bal-fels� sark�nak kezdeti Y koordin�t�ja
		640,						// ablak sz�less�ge
		480,						// �s magass�ga
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);			// megjelen�t�si tulajdons�gok

	// ha nem siker�lt l�trehozni az ablakot, akkor �rjuk ki a hib�t, amit kaptunk �s l�pj�nk ki
	if (win == 0)
	{
		std::cout << "[Ablak l�trehoz�sa]Hiba az SDL inicializ�l�sa k�zben: " << SDL_GetError() << std::endl;
		return 1;
	}
	int WW, WH;
	SDL_GetWindowSize(win, &WW, &WH);


	// imgui init
	ImGui_ImplSdlGL3_Init(win);

	SDL_GLContext	context = SDL_GL_CreateContext(win);
	if (context == 0)
	{
		std::cout << "[OGL context l�trehoz�sa]Hiba az SDL inicializ�l�sa k�zben: " << SDL_GetError() << std::endl;
		return 1;
	}

	// megjelen�t�s: v�rjuk be a vsync-et
	SDL_GL_SetSwapInterval(1);

	// ind�tsuk el a GLEW-t
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << "[GLEW] Hiba az inicializ�l�s sor�n!" << std::endl;
		return 1;
	}

	int glVersion[2] = { -1, -1 };
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
	std::cout << "Running OpenGL " << glVersion[0] << "." << glVersion[1] << std::endl;

	if (glVersion[0] == -1 && glVersion[1] == -1)
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(win);

		std::cout << "[OGL context l�trehoz�sa] Nem siker�lt l�trehozni az OpenGL context-et! Lehet, hogy az SDL_GL_SetAttribute(...) h�v�sokn�l az egyik be�ll�t�s helytelen." << std::endl;

		return 1;
	}

	std::stringstream window_title;
	window_title << "OpenGL " << glVersion[0] << "." << glVersion[1];
	SDL_SetWindowTitle(win, window_title.str().c_str());

	initAudio(); // audio inicializ�l�sa

	{
		bool quit = false;
		SDL_Event ev;

		GameView app;
		if (!app.Init())
		{
			SDL_GL_DeleteContext(context);
			SDL_DestroyWindow(win);
			std::cout << "[app.Init] Az alkalmaz�s inicializ�l�sa k�zben hibat�rt�nt!" << std::endl;
			return 1;
		}

		app.Resize(WW, WH);

		while (!quit)
		{
			// am�g van feldolgozand� �zenet dolgozzuk fel mindet:
			while (SDL_PollEvent(&ev))
			{
				ImGui_ImplSdlGL3_ProcessEvent(&ev);
				bool is_mouse_captured = ImGui::GetIO().WantCaptureMouse;
				bool is_keyboard_captured = ImGui::GetIO().WantCaptureKeyboard;
				switch (ev.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					if (ev.key.keysym.sym == SDLK_ESCAPE && false)
						quit = true;
					if (!is_keyboard_captured)
						app.KeyboardDown(ev.key);
					break;
				case SDL_KEYUP:
					if (!is_keyboard_captured)
						app.KeyboardUp(ev.key);
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (!is_mouse_captured)
						app.MouseDown(ev.button);
					break;
				case SDL_MOUSEBUTTONUP:
					if (!is_mouse_captured)
						app.MouseUp(ev.button);
					break;
				case SDL_MOUSEWHEEL:
					if (!is_mouse_captured)
						app.MouseWheel(ev.wheel);
					break;
				case SDL_MOUSEMOTION:
					if (!is_mouse_captured)
						app.MouseMove(ev.motion);
					break;
				case SDL_WINDOWEVENT:
					if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					{
						app.Resize(ev.window.data1, ev.window.data2);
					}
					break;
				}

			}

			ImGui_ImplSdlGL3_NewFrame(win);
			app.Draw();
			if (app.exitGame()) quit = true;
			ImGui::Render();

			SDL_GL_SwapWindow(win);
		}

		app.Clean();
	}

	ImGui_ImplSdlGL3_Shutdown();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);

	return 0;
}
