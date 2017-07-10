#pragma once
#include <GL/glew.h>
#include <assert.h>
class Mat4
{
public:
	Mat4();
	~Mat4();
	/* Sets the matrix to identity */
	Mat4& setToIdentity();
	/* Puts matrix values into a GLfloat[16] array. Usefull in the processes of sending matrix information to the GPU */
	void Mat4::getValues(GLfloat(&temp)[16]);
	GLfloat & operator()(size_t x, size_t y) { assert(x < 4 && y < 4); return m[x][y]; }
private:
	GLfloat m[4][4];
};

