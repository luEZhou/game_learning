#pragma once

class Vector2 {

public:
	Vector2() = default;
	Vector2(const Vector2&) = default;
	Vector2(Vector2&&) = default;
	~Vector2() = default;

	Vector2& operator=(const Vector2&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2(float x, float y);

	inline float X() const
	{
		return x_;
	}

	inline float Y() const
	{
		return y_;
	}

	inline void setX(float x)
	{
		x_ = x;
	}

	inline void setY(float y)
	{
		y_ = y;
	}

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float scalar) const;
	Vector2 operator/(float scalar) const;
	bool operator==(const Vector2& other) const = default;
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(float scalar);
	Vector2& operator/=(float scalar);

	float length() const;
	float lengthSquared() const;

	void normalize();
	Vector2 normalized() const;

	float dot(const Vector2& rhs) const;

private:
	float x_;
	float y_;
};