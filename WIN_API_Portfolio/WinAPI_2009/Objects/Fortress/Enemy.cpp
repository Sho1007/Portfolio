#include "Framework.h"
#include "Enemy.h"

const float Enemy::MAX_HP = 100.0f;

Enemy::Enemy(Texture* texture)
	: ImageRect(texture), speed(100.0f), direction{0, 1}
{	
	isActive = false;

	animation = new Animation(texture);
	animation->SetDefault(true, true);

	Texture* back = TEXTURE->Add(L"Textures/hpBarTop.bmp", 53, 5);
	Texture* front = TEXTURE->Add(L"Textures/hpBarBottom.bmp", 53, 5);

	hpBar = new HpBar(back, front, MAX_HP);
	hpBar->SetTarget(this);
	hpBar->size = { size.x, size.y / 5.0f };
	hpBar->SetOffset({ 0.0f, -Half().y - hpBar->size.y});
}

Enemy::~Enemy()
{
	delete animation;
	delete hpBar;
}

void Enemy::Update()
{
	if (!isActive)
		return;

	center += direction * speed * DELTA;



	if (Top() > WIN_HEIGHT)
		isActive = false;

	if (Right() < 0.0f || Left() > WIN_WIDTH)
		isActive = false;

	animation->Update();
	hpBar->Update();
}

void Enemy::Render()
{
	if (!isActive)
		return;

	ImageRect::Render(animation->GetFrame());
	hpBar->Render();
}

void Enemy::Spawn(Vector2 pos)
{
	speed = Random(100.0f, 200.0f);
	direction.x = Random(-1.0f, 1.0f);
	direction.y = 1.0f;
	direction.Normalize();

	isActive = true;
	center = pos;

	hpBar->SetHp(MAX_HP);
	animation->Play();
}

void Enemy::Damage(float damage)
{
	hpBar->Damage(damage);
 	EFFECT->Play("exp", center);

	if (hpBar->GetHp() <= 0.0f)
		isActive = false;
}
