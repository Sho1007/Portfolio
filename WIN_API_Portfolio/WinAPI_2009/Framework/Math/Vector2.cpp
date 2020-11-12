#include "Framework.h"

Vector2::Vector2()
	: x(0), y(0)
{
}

Vector2::Vector2(float x, float y)
	: x(x), y(y)
{
}

float Vector2::Length() const
{
	return sqrt(x * x + y * y);
}

float Vector2::SqrLength() const
{
	return x * x + y * y;
}

Vector2 Vector2::Normal() const
{
	return Vector2(x / Length(), y / Length());
}

void Vector2::Normalize()
{
	float length = Length();
	x /= length;
	y /= length;
}

float Vector2::Angle() const
{
	return atan2(-y, x);
}

float Vector2::Cross(const Vector2& value)
{
	return x * value.y - y * value.x;
}
