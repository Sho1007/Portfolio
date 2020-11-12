#pragma once

class Circle : public Object
{
public:
	Vector2 center;
	float radius;

	Circle(Vector2 center, int radius);
	~Circle();

	virtual void Render(HDC hdc) override;
	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(Object* object) override;
	
	virtual bool IsCircleCollision(Circle* circle) override;
	virtual bool IsRectCollision(Rect* rect) override;

	float Left() { return center.x - radius; }
	float Right() { return center.x + radius; }
	float Top() { return center.y - radius; }
	float Bottom() { return center.y + radius; }
};