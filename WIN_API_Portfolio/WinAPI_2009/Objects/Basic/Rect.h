#pragma once

class Rect : public Object
{
public:
	Vector2 center;
	Vector2 size;

	Rect();
	Rect(Vector2 center, Vector2 size);
	Rect(float left, float top, float right, float bottom);
	~Rect();

	virtual void Render(HDC hdc) override;
	virtual bool IsCollision(Vector2 pos) override;	

	virtual bool IsCircleCollision(Circle* circle) override;
	virtual bool IsRectCollision(Rect* rect) override;
	virtual bool IsRectCollision(OUT Rect* overlap, IN Rect* rect);

	void SetRect(float left, float top, float right, float bottom);

	float Left() { return center.x - size.x * 0.5f; }
	float Right() { return center.x + size.x * 0.5f; }
	float Top() { return center.y - size.y * 0.5f; }
	float Bottom() { return center.y + size.y * 0.5f; }

	Vector2 Half() { return size * 0.5f; }
};