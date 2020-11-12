#include "Framework.h"
#include "Circle.h"

Circle::Circle(Vector2 center, int radius)
	: center(center), radius(radius)
{
	type = Type::CIRCLE;
}

Circle::~Circle()
{
}

void Circle::Render(HDC hdc)
{
	if (!isActive)
		return;

	Ellipse(hdc,
		(int)(center.x - radius),
		(int)(center.y - radius),
		(int)(center.x + radius),
		(int)(center.y + radius)
	);
}

bool Circle::IsCollision(Vector2 pos)
{	
	float distance = (pos - center).Length();

	return distance < radius;
}

bool Circle::IsCollision(Object* object)
{
	return Object::IsCollision(object);
}

bool Circle::IsCircleCollision(Circle* circle)
{
	float distance = (center - circle->center).Length();

	return distance < (radius + circle->radius);
}

bool Circle::IsRectCollision(Rect* rect)
{
	return rect->IsCircleCollision(this);
}