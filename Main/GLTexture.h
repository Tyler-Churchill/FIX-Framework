#pragma once
#include <SDL_image.h>
#include <GL\glew.h>
#include <string>
#include <iostream>
class GLTexture
{
public:
	GLTexture(const::std::string& filename);
	void bind(unsigned);
	virtual ~GLTexture();
private:
	GLuint texId;
	unsigned width, height;
};

