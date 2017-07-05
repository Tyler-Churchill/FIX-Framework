#pragma once
#include <SDL_events.h>
class ApplicationListener
{
public:
	virtual ~ApplicationListener() {}
	/* Called once when the game is created */
	virtual void create() = 0;
	/* Called when the window is resized. Paramters: the new width and height of the window. */
	virtual void resize(unsigned width, unsigned height) = 0;
	/* Called once per frame. Parameter: time between frames (ms) */
	virtual void update(double delta) = 0;
	/* Called before update and render. Parameter: the input event */
	virtual void processInput(SDL_Event& e) = 0;
	/* Runs in main thread. Do all rendering calls here. */
	virtual void render() = 0;
};
