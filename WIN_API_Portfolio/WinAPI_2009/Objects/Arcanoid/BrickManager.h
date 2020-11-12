#pragma once
#include "Brick.h"
#include "Ball.h"

class BrickManager
{
private:
	vector<Brick*> bricks;

	HBRUSH brushes[4];
public:
	BrickManager();
	~BrickManager();

	void Render(HDC hdc);

	void CreateStage();
	void ClearStage();

	Direction Collision(Ball* circle);
};