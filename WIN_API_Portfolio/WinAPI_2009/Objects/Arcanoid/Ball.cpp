#include "Framework.h"
#include "Ball.h"

Ball::Ball()
	: Circle({0, 0}, 10), speed(500), direction(1, -1),
	isPlay(false), bar(nullptr), bm(nullptr)
{
	direction.Normalize();

	brush = CreateSolidBrush(WHITE);
}

Ball::~Ball()
{
	DeleteObject(brush);
}

void Ball::Update()
{
	if (KEY_DOWN(VK_SPACE))
		isPlay = true;

	if (!isPlay)
	{
		center.x = bar->center.x;
		center.y = bar->Top() - radius;
	}
	else
	{
		center += direction * speed * DELTA;

		CollisionBorder();
		CollisionBar();
		CollisionBrick();
	}
}

void Ball::Render(HDC hdc)
{
	SelectObject(hdc, brush);
	Circle::Render(hdc);
}

void Ball::CollisionBorder()
{
	if (Left() < 0)
	{
		direction.x *= -1;
		center.x = radius;
	}
	if (Right() > WIN_WIDTH)
	{
		direction.x *= -1;
		center.x = WIN_WIDTH - radius;
	}
	if (Top() < 0)
	{
		direction.y *= -1;
		center.y = radius;
	}
	if (Bottom() > WIN_HEIGHT)
	{
		isPlay = false;
		MessageBox(hWnd, L"GameOver", L"Alram", MB_OK);
		
		direction = { 1, -1 };
		direction.Normalize();

		bm->ClearStage();
		bm->CreateStage();
	}
}

void Ball::CollisionBar()
{
	if (IsCollision(bar))
	{
		Vector2 barBottomCenter;
		barBottomCenter.x = bar->center.x;
		barBottomCenter.y = bar->Bottom();

		direction = (center - barBottomCenter).Normal();
	}
}

void Ball::CollisionBrick()
{
	Direction dir = bm->Collision(this);
	/*
	switch (dir)
	{
	case GameMath::Direction::LEFT:		
	case GameMath::Direction::RIGHT:
		direction.x *= -1;
		break;
	case GameMath::Direction::UP:		
	case GameMath::Direction::DOWN:
		direction.y *= -1;
		break;	
	}*/
}
