#include "Camera.h"

void Camera::update()
{
}

Mat4 & Camera::getProjectionMatrix()
{
	projectionMatrix.setToIdentity();
	GLfloat aspect = (float)viewWidth / (float) viewHeight;
	float yScale = ((1.0f / std::tan((fov / 2.0f) * (float) M_PI / 180.0f)) * aspect);
	float xScale = yScale / aspect;
	float frustLength = zFar - zNear;
	projectionMatrix(0, 0) = xScale;
	projectionMatrix(1, 1) = yScale;
	projectionMatrix(2, 2) = -((zFar + zNear) / frustLength);
	projectionMatrix(2, 3) = -1;
	projectionMatrix(3, 2) = -((2 * zNear * zFar) / frustLength);
	projectionMatrix(3, 3) = 0;
	return projectionMatrix;
}

Mat4 & Camera::getViewMatrix(Vec3 target)
{
	Vec3 vZ = position.sub(target).normalize();
	Vec3 vX = up.cross(vZ).normalize();
	Vec3 vY = vZ.cross(vX);
	viewMatrix(0, 0) = vX.x;
	viewMatrix(0, 1) = vX.y;
	viewMatrix(0, 2) = vX.z;
	viewMatrix(0, 3) = 0;
	viewMatrix(1, 0) = vY.x;
	viewMatrix(1, 1) = vY.y;
	viewMatrix(1, 2) = vY.z;
	viewMatrix(1, 3) = 0;
	viewMatrix(2, 0) = vZ.x;
	viewMatrix(2, 1) = vZ.y;
	viewMatrix(2, 2) = vZ.z;
	viewMatrix(2, 3) = 1;
	return viewMatrix; // probably need to inverse this to actually be useful... we shall see -- I'm still learning
}

Camera::~Camera()
{

}
