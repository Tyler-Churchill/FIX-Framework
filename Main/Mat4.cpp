#include "Mat4.h"



Mat4::Mat4()
{
}


Mat4::~Mat4()
{
}

Mat4 & Mat4::setToIdentity()
{
	m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	return *this;
}

void Mat4::getValues(GLfloat(&temp)[16])
{
	temp[0] = m[0][0]; temp[1] = m[0][1]; temp[2] = m[0][2]; temp[3] = m[0][3];
	temp[4] = m[1][0]; temp[5] = m[1][1]; temp[6] = m[1][2]; temp[7] = m[1][3];
	temp[8] = m[2][0]; temp[9] = m[2][1]; temp[10] = m[2][2]; temp[11] = m[2][3];
	temp[12] = m[3][0]; temp[13] = m[3][1]; temp[14] = m[3][2]; temp[15] = m[3][3];
}
