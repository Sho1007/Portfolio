#pragma once

class Vector2
{
public:
	float x, y;

	Vector2();
	Vector2(float x, float y);

	float Length() const;
	float SqrLength() const;

	Vector2 Normal() const;
	void Normalize();

	float Angle() const;

	Vector2 operator+(const Vector2& value) const
	{
		return Vector2(x + value.x, y + value.y);
	}
	Vector2 operator-(const Vector2& value) const
	{
		return Vector2(x - value.x, y - value.y);
	}
	Vector2 operator*(const float value) const
	{
		return Vector2(x * value, y * value);
	}
	Vector2 operator/(const float value) const
	{
		return Vector2(x / value, y / value);
	}

	void operator+=(const Vector2& value)
	{
		x += value.x;
		y += value.y;
	}
	void operator-=(const Vector2& value)
	{
		x -= value.x;
		y -= value.y;
	}
	void operator*=(const Vector2& value)
	{
		x *= value.x;
		y *= value.y;
	}
	void operator/=(const Vector2& value)
	{
		x /= value.x;
		y /= value.y;
	}


	void operator+=(const float& value)
	{
		x += value;
		y += value;
	}
	void operator-=(const float& value)
	{
		x -= value;
		y -= value;
	}
	void operator*=(const float& value)
	{
		x *= value;
		y *= value;
	}
	void operator/=(const float& value)
	{
		x /= value;
		y /= value;
	}


	float Cross(const Vector2& value);
};