#include "Vec3.h"

Vec3::Vec3(const float& x, const float& y, const float& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vec3::getLength() 
{
	return sqrt(x * x + y * y + z * z);
}

float Vec3::dot(Vec3& other) 
{
	return x * other.x + y * other.y + z * other.z;
}

Vec3& Vec3::normalize() 
{
	float l = getLength();
	x /= l;
	y /= l;
	z /= l;
	return *this;
}

Vec3& Vec3::add(const Vec3& other) 
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3& Vec3::sub(const Vec3& other) 
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3 & Vec3::cross(const Vec3 & other)
{
	float x = y * other.z - z * other.y;
	float y = z * other.x - x * other.z;
	float z = x * other.y - y * other.x;
	return *this;
}

Vec3& Vec3::mul(const Vec3& other) 
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

std::ostream & operator<<(std::ostream & stream, const Vec3 & vector)
{
	return stream << "vec3(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}