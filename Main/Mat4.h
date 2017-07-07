#pragma once
#include <GL/glew.h>
class Mat4
{
public:
	Mat4();
	~Mat4();
	/* Sets the matrix to the identity matrix */
	Mat4& identity();
	/* Puts matrix values into a GLfloat[16] array. Usefull in the processes of sending matrix information to the GPU */
	void Mat4::getValues(GLfloat(&temp)[16]);
private:
	GLfloat m[4][4];
};

