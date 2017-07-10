#pragma once
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
struct {
	SDL_Keysym sym;
	bool pressed;
	uint32_t elapsedTime;
} Button;
class Input
{
public:
	Input();
	~Input();

};

