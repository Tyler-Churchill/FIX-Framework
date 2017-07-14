#include "Camera.h"

void Camera::update()
{
}

Mat4 & Camera::getProjectionMatrix()
{
	m_projectionMatrix.setToIdentity();
	GLfloat aspect = (float)m_viewWidth / (float)m_viewHeight;
	float yScale = ((1.0f / std::tan((m_fov / 2.0f) * (float) M_PI / 180.0f)) * aspect);
	float xScale = yScale / aspect;
	float frustLength = m_zFar - m_zNear;
	m_projectionMatrix(0, 0) = xScale;
	m_projectionMatrix(1, 1) = yScale;
	m_projectionMatrix(2, 2) = -((m_zFar + m_zNear) / frustLength);
	m_projectionMatrix(2, 3) = -1;
	m_projectionMatrix(3, 2) = -((2 * m_zNear * m_zFar) / frustLength);
	m_projectionMatrix(3, 3) = 0;
	return m_projectionMatrix;
}

Mat4 & Camera::getViewMatrix(Vec3 target)
{
	Vec3 vZ = m_position.sub(target).normalize();
	Vec3 vX = m_up.cross(vZ).normalize();
	Vec3 vY = vZ.cross(vX);
	m_viewMatrix(0, 0) = vX.x;
	m_viewMatrix(0, 1) = vX.y;
	m_viewMatrix(0, 2) = vX.z;
	m_viewMatrix(0, 3) = 0;
	m_viewMatrix(1, 0) = vY.x;
	m_viewMatrix(1, 1) = vY.y;
	m_viewMatrix(1, 2) = vY.z;
	m_viewMatrix(1, 3) = 0;
	m_viewMatrix(2, 0) = vZ.x;
	m_viewMatrix(2, 1) = vZ.y;
	m_viewMatrix(2, 2) = vZ.z;
	m_viewMatrix(2, 3) = 1;
	return m_viewMatrix; // probably need to inverse this to actually be useful... we shall see -- I'm still learning
}

Camera::~Camera()
{

}
