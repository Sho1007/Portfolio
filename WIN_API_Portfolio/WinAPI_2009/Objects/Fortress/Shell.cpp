#include "Framework.h"
#include "Shell.h"

Shell::Shell()
	: angle(0), speed(0), isFire(false), gravity(0)
{
	ball = new Circle(Vector2(0, 0), 20);
}

Shell::~Shell()
{
	delete ball;
}

void Shell::Update()
{
	if (!isFire)
		return;

	ball->center.x += cos(angle) * speed * DELTA;
	ball->center.y -= sin(angle) * speed * DELTA;

	gravity += G * DELTA;
	ball->center.y += gravity * DELTA;

	if (ball->center.x < ball->radius)//Left
	{
		angle = PI - angle;
		ball->center.x = ball->radius;
	}
	else if (ball->center.x > WIN_WIDTH - ball->radius)//Right
	{
		angle = PI - angle;
		ball->center.x = WIN_WIDTH - ball->radius;
	}
	else if (ball->center.y < ball->radius)//Top
	{
		angle = 2 * PI - angle;
		ball->center.y = ball->radius;
	}
	else if (ball->center.y > WIN_HEIGHT - ball->radius)//Bottom
	{
		angle = 2 * PI - angle;
		ball->center.y = WIN_HEIGHT - ball->radius;
	}
}

void Shell::Render(HDC hdc)
{
	if (!isFire)
		return;

	ball->Render(hdc);
}

void Shell::Fire(Vector2 pos, float angle, float power)
{
	isFire = true;
	ball->center = pos;
	this->angle = angle;
	speed = power * 0.1f;
	gravity = 0.0f;
}
