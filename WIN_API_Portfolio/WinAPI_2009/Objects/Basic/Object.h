#pragma once

class Circle;
class Rect;

class Object
{
public:
	bool isActive;

	enum class Type
	{
		CIRCLE,
		RECT
	}type;

	Object();

	virtual void Render(HDC hdc) = 0;
	virtual bool IsCollision(Vector2 pos) = 0;	
	virtual bool IsCollision(Object* object);	

	virtual bool IsCircleCollision(Circle* circle) = 0;
	virtual bool IsRectCollision(Rect* rect) = 0;
	virtual bool IsRectCollision(OUT Rect* overlap, IN Rect* rect) { return false; }

	virtual void Damage(float damage) {}
};