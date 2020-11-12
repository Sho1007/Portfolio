#include "Framework.h"

void HWDragonEnemy::Create(UINT enemyType)
{
	this->enemyType = enemyType;

	switch (enemyType)
	{
	case 0:
		texture = TEXTURE->Add(L"Textures/HWShoot/enemy1.bmp", 384, 384, 4, 4);
		speed = 40.0f;
		bulletSpeed = 80.0f;
		bulletPower = 10.0f;
		hpBar->SetHp(400.0f);
		size = { 200, 200 };
		fireDelay = 3.0f;
		break;
	case 1:
		texture = TEXTURE->Add(L"Textures/HWShoot/enemy2.bmp", 356, 364, 4, 4);
		speed = 120.0f;
		bulletSpeed = 300.0f;
		bulletPower = 15.0f;
		hpBar->SetHp(150.0f);
		size = { 100, 100 };
		fireDelay = 1.0f;
		break;
	case 2:
		texture = TEXTURE->Add(L"Textures/HWShoot/enemy3.bmp", 384, 384, 4, 4);
		speed = 70.0f;
		bulletSpeed = 150.0f;
		bulletPower = 30.0f;
		hpBar->SetHp(200.0f);
		size = { 150, 150 };
		fireDelay = 2.0f;
		break;
	}

	hpBar->size = { size.x, 10.0f };
	hpBar->SetOffset({ 0, Half().y + hpBar->size.y });

	bulletFrame = { 0,0 };
	center = { Random(200.0f, WIN_WIDTH - 200.0f), 0 };

	fireTime = fireDelay;

	animation = new Animation(texture);
	animation->SetPart(0, 3, true);
	animation->Play();

	int random = Random(0, 4);
	switch (random)
	{
	case 0:
		velocity.x = 0;
		break;
	case 1:
		velocity.x = 0.25f;
		break;
	case 2:
		velocity.x = 0.5f;
		break;
	case 3:
		velocity.x = 0.75f;
		break;
	}
	velocity.y = 1.0f;

	random = Random(0, 2);

	if (random == 0)
		velocity.x *= -1.0f;
}

void HWDragonEnemy::CreateBoss()
{
	texture = TEXTURE->Add(L"Textures/HWShoot/boss.bmp", 270, 268);
	speed = 40.0f;
	bulletSpeed = 150.0f;
	bulletPower = 20.0f;
	hpBar->SetHp(2000.0f);
	size = { 200, 200 };
	fireDelay = 3.0f;

	hpBar->size = { WIN_WIDTH, 20.0f };
	hpBar->SetOffset({ 0, 0 });
	hpBar->SetTarget(nullptr);
	hpBar->center = { CENTER_X, hpBar->size.y * 0.5f };

	bulletFrame = { 0,0 };
	center = { Random(200.0f, WIN_WIDTH - 200.0f), 0 };

	fireTime = fireDelay;

	velocity.x = 1.0f;
	velocity.y = 1.0f;

	isBoss = true;
}

void HWDragonEnemy::Destroy()
{
	delete hpBar;
	delete animation;
}

void HWDragonEnemy::Fire()
{
	if (fireTime > 0.0f)
		fireTime -= DELTA;
	if (fireTime <= 0.0f)
	{
		Vector2 dir = player->center - center;
		float angle = atan2(-dir.y, dir.x);
		switch (enemyType)
		{
		case 0:
			AUDIO->Play("enemyShot1");
			break;
		case 1:
			AUDIO->Play("enemyShot2");
			break;
		case 2:
			AUDIO->Play("enemyShot3");
			break;

		}
		fireTime = fireDelay;
		bm->Fire("enemy", center, angle, bulletSpeed, bulletPower, bulletFrame);
	}
}

void HWDragonEnemy::FireBoss()
{
	if (fireTime > 0.0f)
		fireTime -= DELTA;
	if (fireTime <= 0.0f)
	{
		float  angle = 0;
		fireTime = fireDelay;
		for (UINT i = 0; i < 20; ++i)
		{
			bm->Fire("enemy", center, angle, bulletSpeed, bulletPower, bulletFrame);
			angle += PI / 10;
		}
	}
	
}

HWDragonEnemy::HWDragonEnemy()
	: isBoss(false)
{
	Texture* back = TEXTURE->Add(L"Textures/hpBarTop.bmp", 53, 5);
	Texture* front = TEXTURE->Add(L"Textures/hpBarBottom.bmp", 53, 5);
	hpBar = new HpBar(back, front, 100.0f);
	hpBar->SetTarget(this);
}

HWDragonEnemy::~HWDragonEnemy()
{
	Destroy();
}

void HWDragonEnemy::Update()
{
	if (isBoss && center.y > 200.0f)
		velocity.y = 0;
	animation->Update();
	if (!isBoss)
		Fire();
	else
		FireBoss();

	center += velocity * speed * DELTA;

	if (Left() < 0)
	{
		velocity.x *= -1;
		center.x = Half().x;
	}
	else if (Right() > WIN_WIDTH)
	{
		velocity.x *= -1;
		center.x = WIN_WIDTH - Half().x;
	}
	if (Top() > WIN_HEIGHT)
	{
		isActive = false;
	}
	hpBar->Update();
}

void HWDragonEnemy::Render()
{
	if (!isBoss)
		ImageRect::Render(animation->GetFrame());
	else
		ImageRect::Render();
	hpBar->Render();
}
