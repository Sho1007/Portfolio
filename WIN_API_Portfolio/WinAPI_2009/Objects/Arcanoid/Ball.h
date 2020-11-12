#pragma once
#include "BrickManager.h"

class Ball : public Circle
{
private:
	float speed;
	Vector2 direction;

	bool isPlay;

	Rect* bar;
	BrickManager* bm;

	HBRUSH brush;
public:
	Ball();
	~Ball();

	void Update();
	void Render(HDC hdc);

	void CollisionBorder();
	void CollisionBar();
	void CollisionBrick();

	void SetBar(Rect* value) { bar = value; }
	void SetBM(BrickManager* value) { bm = value; }

	Vector2* GetDirection() { return&direction; }
};