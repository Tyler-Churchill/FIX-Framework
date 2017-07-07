#include "Application.h"

Application::Application(ApplicationListener& game, Configuration& configuration) : game(game), configuration(configuration)
{
	if (initialize()) 
	{
		mainLoop();
	}
	else
	{
		exit();
	}
}

Application::~Application()
{
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

bool Application::initialize() {
	switch (configuration.renderer) 
	{
	case Configuration::RENDER_ENGINE::OPENGL:
		if (!initOpenGL())
		{
			return false;
		}
		break; /* end OpenGL system initialization */
	case Configuration::RENDER_ENGINE::SOFTWARE: default:
		break; /* end Software system initialization */
	}
	running = true;
	return true;
}

bool Application::initOpenGL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		log(SDL_GetError()); return false;
	} 
	else 
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		const char * tempTitle = configuration.title.c_str();
		window = SDL_CreateWindow(tempTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, configuration.width, configuration.height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			log(SDL_GetError()); return false;
		}
		else
		{
			glContext = SDL_GL_CreateContext(window);
			if (glContext == nullptr) 
			{
				log(SDL_GetError()); return false;
			}
			else
			{
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					log(glewGetErrorString(glewError));
				}
				if (!configuration.vSync) 
				{
					if (SDL_GL_SetSwapInterval(0) < 0) log(SDL_GetError());
				}
				else 
				{
					if (SDL_GL_SetSwapInterval(1) < 0) log(SDL_GetError());
				}
				if (configuration.fullscreen) 
				{
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
			}
		}
	}
#if DEBUG
	log("---------------" + configuration.title + "---------------");
	std::cout << "    vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "  renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "   version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "   resolution: " << configuration.width << "x" << configuration.height << std::endl;
	std::cout << "   vSync: " << configuration.vSync << std::endl;
	std::cout << "   fullscreen: " << configuration.fullscreen << std::endl;
	std::cout << "---------------------------------" << std::endl << std::endl;
#endif
	return true;
}

void Application::mainLoop() {
	// read user input
	// animate actors
	// check collisions
	// run ai
	// play music
	game.create();
	SDL_Event e;
	do 
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				exit();
			}
		}
		curTime = SDL_GetTicks();
		delta = (curTime - lastTime) / 1000;
		lastTime = curTime;
		if (curTime - startTime >= 1000)
		{
			fps = frames;
			frames = 0;
			startTime = curTime;
		}
		frames++;
		game.processInput(e);
		update();
		render();
		SDL_GL_SwapWindow(window);
		log(curTime);
	} while (running);
}
void Application::update()
{
	game.update(delta);
}

void Application::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	game.render();
}
