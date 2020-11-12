#include "Framework.h"
#include "Player.h"

void Player::Create()
{
	key = DataManager::Get()->GetSelectNum();
	PlayerData* data = DataManager::Get()->GetPlayerData()[key];

	texture = TEXTURE->Find(ToWString(data->image));

	attack = data->attack;
	speed = data->speed;
	accel = data->accel;

	size = { 70, 70 };

	Texture* back = TEXTURE->Add(L"Textures/hpBarTop.bmp", 53, 5);
	Texture* front = TEXTURE->Add(L"Textures/hpBarBottom.bmp", 53, 5);
	hpBar = new HpBar(back, front, data->hp);
	hpBar->SetTarget(this);
	hpBar->size = { this->size.x, this->size.y * 0.2f };
	hpBar->SetOffset({ 0, Half().y });
}

Player::Player()
{
	Create();
	center = { CENTER_X, WIN_HEIGHT * 0.8f };
}

Player::~Player()
{
}

void Player::Update()
{
	Move();
	Fire();
	hpBar->Update();
}

void Player::Redner()
{
	ImageRect::Render();
	hpBar->Render();
}

void Player::Move()
{
	bool isPressKey = false;
	if (KEY_PRESS(VK_RIGHT))
	{
		isPressKey = true;
		velocity.x += accel * DELTA;
		velocity.x = min(velocity.x, MAX_SPEED);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		isPressKey = true;
		velocity.x -= accel * DELTA;
		velocity.x = max(velocity.x, -MAX_SPEED);
	}
	if (KEY_PRESS(VK_UP))
	{
		isPressKey = true;
		velocity.y -= accel * DELTA;
		velocity.y = max(velocity.y, -MAX_SPEED);
	}
	if (KEY_PRESS(VK_DOWN))
	{
		isPressKey = true;
		velocity.y += accel * DELTA;
		velocity.y = min(velocity.y, MAX_SPEED);
	}

	if (!isPressKey)
	{
		if (velocity.x > 0.0f)
		{
			velocity.x -= accel * DELTA;
			if (velocity.x < 0.0f)
				velocity.x = 0.0f;
		}
		else if (velocity.x < 0.0f)
		{
			velocity.x += accel * DELTA;
			if (velocity.x > 0.0f)
				velocity.x = 0.0f;
		}

		if (velocity.y > 0.0f)
		{
			velocity.y -= accel * DELTA;
			if (velocity.y < 0.0f)
				velocity.y = 0.0f;
		}
		else if (velocity.y < 0.0f)
		{
			velocity.y += accel * DELTA;
			if (velocity.y > 0.0f)
				velocity.y = 0.0f;
		}
	}

	center += velocity * speed * DELTA;

	if (key == 1)
	{
		if (velocity.x > 0)
			frame.x = 2;
		else if (velocity.x < 0)
			frame.x = 0;
		else
			frame.x = 1;
	}

	if (Left() < 0)
	{
		center.x = Half().x;
		velocity.x = 0.0f;
	}
	else if (Right() > WIN_WIDTH)
	{
		center.x = WIN_WIDTH - Half().x;
		velocity.x = 0.0f;
	}

	if (Top() < 0)
	{
		center.y = Half().y;
		velocity.y = 0.0f;
	}
	else if (Bottom() > WIN_HEIGHT)
	{
		center.y = WIN_HEIGHT - Half().y;
		velocity.y = 0.0f;
	}
}

void Player::Fire()
{
	if (KEY_DOWN(VK_SPACE))
	{
		switch (key)
		{
		case 1 :
			bm->Fire("player", center, PI * 0.5f, BULLET_SPEED, attack);
			break;
		case 2:
			bm->Fire("player", center, PI * 0.5f, BULLET_SPEED, attack);
			bm->Fire("player", center, PI * 0.5f - 0.1f, BULLET_SPEED, attack);
			bm->Fire("player", center, PI * 0.5f + 0.1f, BULLET_SPEED, attack);
			break;
		case 3:
			{
				Vector2 pos = center;
				pos.x -= 50;
				bm->Fire("player", pos, PI * 0.5f, BULLET_SPEED, attack);
				pos.x += 100;
				bm->Fire("player", pos, PI * 0.5f, BULLET_SPEED, attack);
			}
			
		}
		
	}
}
