#pragma once
#include <iostream>
#include <GL\glew.h>
class Vec3
{
public:
	Vec3() : x(0), y(0), z(0) {};
	~Vec3() {};
	Vec3(const float& x, const float& y, const float& z);
	float getLength();
	float dot(Vec3& other);
	Vec3& normalize();
	Vec3& add(const Vec3& other);
	Vec3& mul(const Vec3& other);
	Vec3& sub(const Vec3& other);
	Vec3& cross(const Vec3& other);
	const float & getX() const { return x; };
	const float & getY() const { return y; };
	const float & getZ() const { return z; };
	void setX(float x) { this->x = x; };
	void setY(float y) { this->y = y; };
	void setZ(float z) { this->z = z; };
	friend std::ostream& operator<<(std::ostream& stream, const Vec3& vector);
	GLfloat x, y, z;
};

