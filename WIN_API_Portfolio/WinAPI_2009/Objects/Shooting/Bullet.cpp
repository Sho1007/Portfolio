#include "Framework.h"

Bullet::Bullet(Texture* texture)
	: ImageRect(texture)
{
	isActive = false;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (!isActive)
		return;

	center.x += cos(angle) * speed * DELTA;
	center.y -= sin(angle) * speed * DELTA;

	if (Right() < 0.0f || Bottom() < 0.0f)
		isActive = false;
	if (Left() > WIN_WIDTH || Top() > WIN_HEIGHT)
		isActive = false;
}

void Bullet::Render()
{
	if (!isActive)
		return;
	ImageRect::Render();
}

void Bullet::Fire(const Vector2 pos, const float angle, const float speed, const float damage)
{
	isActive = true;

	center = pos;
	this->angle = angle;
	this->speed = speed;
	this->damage = damage;
}
