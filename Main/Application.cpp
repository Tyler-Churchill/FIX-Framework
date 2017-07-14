#include "Application.h"

Application::Application(ApplicationListener& game, Configuration& configuration) : m_game(game), m_configuration(configuration)
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
	if (m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
	IMG_Quit();
	SDL_Quit();
}

bool Application::initialize() {
	if (m_configuration.renderer == RENDER_ENGINE::OPENGL)
	{
		if (!initOpenGL())
		{
			return false;
		}
	}
    if (m_configuration.renderer == RENDER_ENGINE::COMPATIBILITY)
	{
		if (!initCompatibility())
		{
			return false;
		}
	}
	m_running = true;
	return true;
}

bool Application::initOpenGL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		log(SDL_GetError()); return false;
	} 
	else 
	{
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			log(IMG_GetError()); return false;
		}
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		const char * tempTitle = m_configuration.title.c_str();
		m_window = SDL_CreateWindow(tempTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_configuration.width, m_configuration.height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (m_window == nullptr)
		{
			log(SDL_GetError()); return false;
		}
		else
		{
			m_glContext = SDL_GL_CreateContext(m_window);
			if (m_glContext == nullptr) 
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
				if (!m_configuration.vSync)
				{
					if (SDL_GL_SetSwapInterval(0) < 0) log(SDL_GetError());
				}
				else 
				{
					if (SDL_GL_SetSwapInterval(1) < 0) log(SDL_GetError());
				}
				if (m_configuration.fullscreen)
				{
					SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
			}
		}
	}
#if DEBUG
	log("---------------" + m_configuration.title + "---------------");
	std::cout << "    vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "  renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "   version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "   resolution: " << m_configuration.width << "x" << m_configuration.height << std::endl;
	std::cout << "   vSync: " << m_configuration.vSync << std::endl;
	std::cout << "   fullscreen: " << m_configuration.fullscreen << std::endl;
	std::cout << "---------------------------------" << std::endl << std::endl;
#endif
	return true;
}

bool Application::initCompatibility()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		log(SDL_GetError()); return false;
	}
	else 
	{
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			log(IMG_GetError()); return false;
		}
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) // linear texture filtering
		{
			log(SDL_GetError()); return false;
		}
		const char * tempTitle = m_configuration.title.c_str();
		m_window = SDL_CreateWindow(tempTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_configuration.width, m_configuration.height, SDL_WINDOW_SHOWN);
		if (m_window == nullptr)
		{
			log(SDL_GetError()); return false;
		}
		else
		{

			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
			if(m_renderer == nullptr)
			{
				log(SDL_GetError()); return false;
			}
			else
			{
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				
			}
		}
	}
	return true;
}

void Application::mainLoop() {
	// read user input
	// animate actors
	// check collisions
	// run ai
	// play music
	m_game.create();
	InputEvent e;
	do 
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				exit();
			}
			switch (e.type) {
			case SDL_QUIT:
				exit();
				break;
			case SDL_KEYDOWN: case SDL_KEYUP:
				m_game.keyboardInput(e);
				break;
			case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP: case SDL_MOUSEWHEEL:
				m_game.mouseInput(e);
				break;
			}
		}
		m_curTime = SDL_GetTicks();
		m_delta = (m_curTime - m_lastTime) / 1000;
		m_lastTime = m_curTime;
		if (m_curTime - m_startTime >= 1000)
		{
			m_fps = m_frames;
			m_frames = 0;
			m_startTime = m_curTime;
		}
		m_frames++;
		update();
		render();
		if (m_configuration.renderer == RENDER_ENGINE::OPENGL)
		{
			SDL_GL_SwapWindow(m_window);
		}
		if (m_configuration.renderer == RENDER_ENGINE::COMPATIBILITY)
		{
			SDL_UpdateWindowSurface(m_window);
		}
	} while (m_running);
}

void Application::update()
{
	m_game.update(m_delta);
}

void Application::render()
{
	m_game.render();
	if (m_configuration.renderer == RENDER_ENGINE::COMPATIBILITY)
	{
		SDL_RenderClear(m_renderer);

		SDL_RenderPresent(m_renderer);
	}
}
