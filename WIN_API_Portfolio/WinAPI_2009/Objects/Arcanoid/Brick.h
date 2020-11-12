#pragma once

class Ball;

class Brick : public Rect
{
private:
	int hp;
	
	HBRUSH* brushes;
public:
	Brick(Vector2 pos, Vector2 size, int hp = 1);
	~Brick();

	void Render(HDC hdc);

	Direction Collision(Circle* circle);
	bool Collision(Ball* ball);

	int GetHp() { return hp; }
	void SetBrush(HBRUSH* value) { brushes = value; }
};