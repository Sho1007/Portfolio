#include "Framework.h"

HWDragonPlayer::HWDragonPlayer()
	: speed(200.0f), attack(50.0f), fireDelay(0.5f), fireTime(0.0f)
{
	Create();
}

HWDragonPlayer::~HWDragonPlayer()
{
	Destroy();
}

void HWDragonPlayer::Update()
{
	bm->Update();
	bm->IsCollision("enemy", this);
	hpBar->Update();
	animation->Update();
	Move();
	Fire();
}

void HWDragonPlayer::Render()
{
	bm->Render();
	ImageRect::Render(animation->GetFrame());
	hpBar->Render();
}

void HWDragonPlayer::GetPowerUp()
{
	if (powerState < 3)
	{
		powerState++;
		SetPowerState(powerState);
	}
}

void HWDragonPlayer::Damage(float dmg)
{
	hpBar->Damage(dmg);
	if (hpBar->GetHp() <= 0.0f)
	{
		MessageBox(hWnd, L"GameOver", L"Alram", MB_OK);
		PostQuitMessage(0);
	}
}

void HWDragonPlayer::Create()
{
	atkState = NONE;
	powerState = 0;
	SetPowerState(powerState);

	texture = TEXTURE->Add(L"Textures/HWShoot/dragon1.bmp", 512, 512, 4, 4);

	size = { 100, 100 };

	center = { CENTER_X, WIN_HEIGHT * 0.8f };

	animation = new Animation(texture);
	animation->SetPart(12, 15, true);
	animation->Play();

	Texture* back = TEXTURE->Add(L"Textures/hpBarTop.bmp", 53, 5);
	Texture* front = TEXTURE->Add(L"Textures/hpBarBottom.bmp", 53, 5);
	hpBar = new HpBar(back, front, 100.0f);
	hpBar->SetTarget(this);
	hpBar->size = { this->size.x, 10.0f };
	hpBar->SetOffset({ 0, Half().y + hpBar->size.y });
}

void HWDragonPlayer::Destroy()
{
	delete animation;
}

void HWDragonPlayer::Move()
{
	if (KEY_DOWN(VK_LEFT))
	{
		velocity.x -= 1.0f;
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		velocity.x += 1.0f;
	}
	if (KEY_DOWN(VK_UP))
	{
		velocity.y -= 1.0f;
	}
	if (KEY_DOWN(VK_DOWN))
	{
		velocity.y += 1.0f;
	}

	if (KEY_UP(VK_LEFT))
	{
		velocity.x += 1.0f;
	}
	if (KEY_UP(VK_RIGHT))
	{
		velocity.x -= 1.0f;
	}
	if (KEY_UP(VK_UP))
	{
		velocity.y += 1.0f;
	}
	if (KEY_UP(VK_DOWN))
	{
		velocity.y -= 1.0f;
	}

	center += velocity * speed * DELTA;

	if (Left() < 0)
		center.x = Half().x;
	else if (Right() > WIN_WIDTH)
		center.x = WIN_WIDTH - Half().x;

	if (Top() < 0)
		center.y = Half().y;
	else if (Bottom() > WIN_HEIGHT)
		center.y = WIN_HEIGHT - Half().y;
}

void HWDragonPlayer::Fire()
{
	if (fireTime > 0.0f)
		fireTime -= DELTA;

	if (KEY_PRESS(VK_SPACE))
	{
		if (fireTime <= 0.0f)
		{
			AUDIO->Play("shot");
			fireTime = fireDelay;

			switch (atkState)
			{
			case NONE:
				bm->Fire("player", center, PI * 0.5f, bulletSpeed, bulletPower, bulletFrame);
				break;
			case DOUBLE:
				bm->Fire("player", {center.x - 10.0f, center.y}, PI * 0.5f, bulletSpeed, bulletPower, bulletFrame);
				bm->Fire("player", { center.x + 10.0f, center.y }, PI * 0.5f, bulletSpeed, bulletPower, bulletFrame);
				break;
			case TRIPLE:
				bm->Fire("player", { center.x - 20.0f, center.y }, PI * 0.5f, bulletSpeed, bulletPower, bulletFrame);
				bm->Fire("player", center, PI * 0.5f, bulletSpeed, bulletPower, bulletFrame);
				bm->Fire("player", { center.x + 20.0f, center.y }, PI * 0.5f, bulletSpeed, bulletPower, bulletFrame);
				break;
			}
		}
	}
}

void HWDragonPlayer::SetPowerState(UINT value)
{
	switch (powerState)
	{
	case 0:
		bulletSpeed = 200.0f;
		bulletPower = 30.0f;
		bulletFrame = { 0, 0 };
		break;
	case 1:
		bulletSpeed = 250.0f;
		bulletPower = 50.0f;
		bulletFrame = { 1, 0 };
		break;
	case 2:
		bulletSpeed = 300.0f;
		bulletPower = 80.0f;
		bulletFrame = { 2, 0 };
		break;
	case 3:
		bulletSpeed = 350.0f;
		bulletPower = 100.0f;
		bulletFrame = { 3, 0 };
		break;
	}
}


