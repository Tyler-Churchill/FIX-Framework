#ifndef _APPLICATION_H
#define _APPLICATION_H

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
#include "AssetManager.h"
#include "ApplicationListener.h"

#define DEBUG 1
#if DEBUG
	#define log(x) std::cout << x << std::endl
#endif

typedef SDL_Event InputEvent;
typedef SDL_Keycode KeyCode;

enum RENDER_ENGINE { OPENGL, COMPATIBILITY };

struct Configuration {
	std::string title { "FIX FRAMEWORK" };
	unsigned width{ 1600 }, height{ 1000 }, inputPollingRate{ 10 }; // times per second
	bool fullscreen{ false }, vSync{ true };
	RENDER_ENGINE renderer{ RENDER_ENGINE::OPENGL };
};

class Application
{
public:
	Application(ApplicationListener& game, Configuration& configuration);
	~Application();
	inline SDL_Window* getWindow() { return m_window; }
	inline const Configuration getConfiguration() const { return m_configuration; }
	inline void exit() { m_running = false; };
protected:
	void mainLoop();
	void update();
	void render();
	ApplicationListener& m_game;
	std::atomic_bool m_running;
private:
	/* Initializes the application with the current configuration passed into Application()*/
	bool initialize();
	/* Initializes OpenGL context rendering. Returns true if successful.*/
	bool initOpenGL();
	/* Initializes the SDL2 compatibility rendering (D3D, OpenGL, OpenGLES)  . Return true if successful. */
	bool initCompatibility();
	Configuration m_configuration;
	AssetManager m_assetManager;
	double m_delta{ 0 };
	uint32_t m_frames{ 0 };
	uint32_t m_startTime{ 0 };
	uint32_t m_lastTime{ 0 };
	uint32_t m_curTime{ 0 };
	uint32_t m_fps{ 0 };
	SDL_Window *m_window{ nullptr };
	SDL_GLContext m_glContext{ nullptr };
	SDL_Surface *m_screenSurface{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
	std::string FIX_VERSION {"0.0.1v"};
};
#endif
