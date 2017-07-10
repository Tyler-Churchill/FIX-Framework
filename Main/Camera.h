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
	Camera(unsigned viewWidth, unsigned viewHeight, GLfloat posX, GLfloat posY, GLfloat posZ) : viewWidth(viewWidth), viewHeight(viewHeight), position(posX, posY, posZ) {}
	void update();
	Mat4& getProjectionMatrix();
	Mat4& getViewMatrix(Vec3 target);
	~Camera();
private:
	GLuint viewWidth;
	GLuint viewHeight;
	Vec3 position{ 0, 0, 0 };
	Vec3 forward{ 0, 0, 1 };
	Vec3 up{ 0, 1, 0 };
	GLfloat zNear{ 0.1f };
	GLfloat zFar{ 10.0f };
	GLfloat fov{ 65.0f };
	Mat4 viewMatrix;
	Mat4 projectionMatrix;
};

