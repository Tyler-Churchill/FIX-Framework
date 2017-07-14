#pragma once
#include <GL\glew.h>
#include <GL\GLU.h>
#include "Vec3.h"
#include "Mat4.h"
#include <SDL_stdinc.h>
#include <cmath>
class Camera
{
	enum ViewMode { ORTHOGRAPHIC, PROJECTION };
public:
	Camera(unsigned viewWidth, unsigned viewHeight, GLfloat posX, GLfloat posY, GLfloat posZ) : m_viewWidth(viewWidth), m_viewHeight(viewHeight), m_position(posX, posY, posZ) {}
	void update();
	Mat4& getProjectionMatrix();
	Mat4& getViewMatrix(Vec3 target);
	~Camera();
private:
	GLuint m_viewWidth;
	GLuint m_viewHeight;
	Vec3 m_position{ 0, 0, 0 };
	Vec3 m_forward{ 0, 0, 1 };
	Vec3 m_up{ 0, 1, 0 };
	GLfloat m_zNear{ 0.1f };
	GLfloat m_zFar{ 10.0f };
	GLfloat m_fov{ 65.0f };
	Mat4 m_viewMatrix;
	Mat4 m_projectionMatrix;
};

