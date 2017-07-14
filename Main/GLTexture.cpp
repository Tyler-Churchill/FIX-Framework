#include "GLTexture.h"

GLTexture::GLTexture(const std::string& fileName)
{
	SDL_Surface *textureData = nullptr;
	std::string loc = "..//assets//textures//" + fileName;
	textureData = IMG_Load(loc.c_str());
	if (textureData == nullptr)
	{
		std::cerr << "Texture load failed: " << loc << std::endl;
	}
	glGenTextures(1, &m_texId);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	// width and height wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// linear interpolation
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData->w, textureData->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData->pixels);
	SDL_FreeSurface(textureData);
}

void GLTexture::bind(unsigned n)
{
	SDL_assert(n >= 0 && n <= 31);
	glActiveTexture(GL_TEXTURE0 + n);
	glBindTexture(GL_TEXTURE_2D, m_texId);
}

GLTexture::~GLTexture()
{
	glDeleteTextures(1, &m_texId);
}
