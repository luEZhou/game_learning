#include "Vector2.h"

#include <cmath>

Vector2::Vector2(float x, float y) : x_(x), y_(y)
{
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	Vector2 result{*this};
	result += rhs;
	return result;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x_ += rhs.x_;
	y_ += rhs.y_;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x_ -= rhs.x_;
	y_ -= rhs.y_;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	Vector2 result{*this};
	result -= rhs;
	return result;
}

Vector2 Vector2::operator*(float scalar) const
{
	Vector2 result{*this};
	result *= scalar;
	return result;
}

Vector2& Vector2::operator*=(float scalar)
{
	x_ *= scalar;
	y_ *= scalar;
	return *this;
}

Vector2 Vector2::operator/(float scalar) const
{
	Vector2 result{*this};
	result /= scalar;
	return result;
}

Vector2& Vector2::operator/=(float scalar)
{
	x_ /= scalar;
	y_ /= scalar;
	return *this;
}

float Vector2::length() const
{
	return std::sqrt(x_ * x_ + y_ * y_);
}

float Vector2::lengthSquared() const
{
	return x_ * x_ + y_ * y_;
}

void Vector2::normalize()
{
	float len = length();
	if (len > 0.0f) {
		x_ /= len;
		y_ /= len;
	}
}

Vector2 Vector2::normalized() const
{
	Vector2 result{*this};
	result.normalize();
	return result;
}

float Vector2::dot(const Vector2& rhs) const
{
	return x_ * rhs.x_ + y_ * rhs.y_;
}