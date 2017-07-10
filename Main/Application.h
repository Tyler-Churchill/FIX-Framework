#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <atomic>
#include <thread>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include "ApplicationListener.h"

#define DEBUG 1
#if DEBUG
	#define log(x) std::cout << x << std::endl
#endif

typedef SDL_Event InputEvent;
typedef SDL_Keycode KeyCode;

enum RENDER_ENGINE { OPENGL, SOFTWARE };

struct Configuration {
	std::string title { "FIX FRAMEWORK" };
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
	/* Initializes the application with the current configuration passed into Application()*/
	bool initialize();
	/* Initializes OpenGL context. Returns true if successful.*/
	bool initOpenGL();
	/* Initializes the software rendering context. Return true if successful. */
	bool initSoftware();
	Configuration configuration;
	double delta{ 0 };
	uint32_t frames{ 0 };
	uint32_t startTime{ 0 };
	uint32_t lastTime{ 0 };
	uint32_t curTime{ 0 };
	uint32_t fps{ 0 };
	SDL_Window *window{ nullptr };
	SDL_GLContext glContext{ nullptr };
	SDL_Surface *screenSurface{ nullptr };
	std::string FIX_VERSION {"0.0.1v"};
};

