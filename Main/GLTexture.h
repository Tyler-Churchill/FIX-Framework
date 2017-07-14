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
	GLuint m_texId;
	unsigned m_width, m_height;
};

