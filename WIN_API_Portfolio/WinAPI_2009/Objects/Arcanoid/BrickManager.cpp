#include "Framework.h"
#include "BrickManager.h"

BrickManager::BrickManager()
{
	brushes[0] = CreateSolidBrush(RED);
	brushes[1] = CreateSolidBrush(BLUE);
	brushes[2] = CreateSolidBrush(GREEN);
	brushes[3] = CreateSolidBrush(YELLOW);

	CreateStage();
}

BrickManager::~BrickManager()
{
	ClearStage();
}

void BrickManager::Render(HDC hdc)
{
	for (Brick* brick : bricks)
		brick->Render(hdc);
}

void BrickManager::CreateStage()
{
	int width = 10;
	int height = 4;

	Vector2 size = { WIN_WIDTH / (float)width,
		WIN_HEIGHT / (float)height * 0.2f };

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width ; x++)
		{
			Vector2 pos;
			pos.x = x * size.x + size.x * 0.5f;
			pos.y = y * size.y + size.y * 0.5f;

			Brick* brick = new Brick(pos, size, height - y);
			brick->SetBrush(brushes);
			bricks.emplace_back(brick);
		}
	}
}

void BrickManager::ClearStage()
{
	for (Brick* brick : bricks)
		delete brick;

	bricks.clear();
}

Direction BrickManager::Collision(Ball* circle)
{
	for (Brick* brick : bricks)
	{
		//Direction dir = brick->Collision(circle);
		//if (dir != Direction::NONE)
			//return dir;
		if (brick->Collision(circle))
			return Direction::NONE;
	}

	return Direction::NONE;
}
