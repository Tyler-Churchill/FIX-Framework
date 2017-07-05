#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <atomic>
#include <thread>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "ApplicationListener.h"

#define DEBUG 1
#if DEBUG
	#define log(x) std::cout << x << std::endl
#endif

struct Configuration {
	enum RENDER_ENGINE { OPENGL, SOFTWARE };
	std::string title { "FIX ENGINE" };
	unsigned width{ 800u }, height{ 800u };
	bool fullscreen{ false }, vSync{ false };
	RENDER_ENGINE renderer{ RENDER_ENGINE::OPENGL };
};

class Application
{
public:
	Application(ApplicationListener& game, Configuration& configuration);
	~Application();
	void exit() { running = false; };
protected:
	void mainLoop();
	void update();
	void render();
	ApplicationListener& game;
	std::atomic_bool running;
private:
	bool initialize();
	bool initOpenGL();
	Configuration configuration;
	double delta{ 0 };
	Uint16 frames{ 0 };
	Uint32 startTime{ 0 };
	Uint32 lastTime{ 0 };
	Uint32 curTime{ 0 };
	Uint16 fps;
	SDL_Window *window{ nullptr };
	SDL_GLContext glContext{ nullptr };
	std::string FIX_VERSION {"0.0.1v"};
};

