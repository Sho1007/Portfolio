#include "Framework.h"
#include "Player.h"

void Player::Create()
{
	state = IDLE;
	/*key = DataManager::Get()->GetSelectNum();
	PlayerData* data = DataManager::Get()->GetPlayerData()[key];*/

	/*texture = TEXTURE->Find(ToWString(data->image));*/

	texture = TEXTURE->Add(L"Textures/charTest.bmp", 144, 320, 3, 4);

	/*attack = data->attack;
	speed = data->speed;
	accel = data->accel;*/

	CreateActions();
	animations[IDLE]->Play();

	speed = 100.0f;

	size = { 120, 120 };

	Texture* back = TEXTURE->Add(L"Textures/hpBarTop.bmp", 53, 5);
	Texture* front = TEXTURE->Add(L"Textures/hpBarBottom.bmp", 53, 5);
	hpBar = new HpBar(back, front, 100);
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
	for (Animation* animation : animations)
	{
		delete animation;
	}
}

void Player::Update()
{
	DoAction();
	Move();
	Fire();
	hpBar->Update();
	animations[state]->Update();
}

void Player::Redner()
{
	ImageRect::Render(animations[state]->GetFrame());
	//hpBar->Render();
}

void Player::Move()
{
	bool isPressKey = false;
	if (KEY_PRESS(VK_RIGHT))
	{
		isPressKey = true;
		velocity.x = 1.0f;
	}
	if (KEY_PRESS(VK_LEFT))
	{
		isPressKey = true;
		velocity.x = -1.0f;
	}
	if (KEY_PRESS(VK_UP))
	{
		isPressKey = true;
		velocity.y = -1.0f;
	}
	if (KEY_PRESS(VK_DOWN))
	{
		isPressKey = true;
		velocity.y = 1.0f;
	}

	if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT))
		velocity.x = 0;
	if (KEY_UP(VK_UP) || KEY_UP(VK_DOWN))
		velocity.y = 0;

	if (velocity.Length() >= 1.0f)
		velocity.Normalize();

	if (abs(velocity.x) >= abs(velocity.y))
	{
		if (velocity.x < 0)
		{
			SetAnimation(LEFT_WALK);
		}
		else if (velocity.x > 0)
		{
			SetAnimation(RIGHT_WALK);
		}
	}
	else
	{
		if (velocity.y > 0)
		{
			SetAnimation(FRONT_WALK);
		}
		else if (velocity.y < 0)
		{
			SetAnimation(BACK_WALK);
		}
	}
	center += velocity * speed * DELTA;

	if (velocity.x == 0 && velocity.y == 0)
	{
		if (state == LEFT_WALK)
			SetAnimation(LEFT);
		else if (state == RIGHT_WALK)
			SetAnimation(RIGHT);
		else if (state == BACK_WALK)
			SetAnimation(BACK);
		else if (state == FRONT_WALK)
			SetAnimation(IDLE);
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

void Player::CreateActions()
{
	//	IDLE
	animations.emplace_back(new Animation(texture));
	animations[IDLE]->SetPart(0, 0, true);

	//	WALK_FRONT
	animations.emplace_back(new Animation(texture, 0.3f));
	animations[FRONT_WALK]->SetPart(1, 2, true);

	//	LEFT
	animations.emplace_back(new Animation(texture));
	animations[LEFT]->SetPart(3, 3, true);

	//	WALK_LEFT
	animations.emplace_back(new Animation(texture, 0.3f));
	animations[LEFT_WALK]->SetPart(4, 5, true);

	//	RIGHT
	animations.emplace_back(new Animation(texture));
	animations[RIGHT]->SetPart(6, 6, true);

	//	WALK_RIGHT
	animations.emplace_back(new Animation(texture, 0.3f));
	animations[RIGHT_WALK]->SetPart(7, 8, true);

	//	BACK
	animations.emplace_back(new Animation(texture));
	animations[BACK]->SetPart(9, 9, true);

	//	WAKL_BACK
	animations.emplace_back(new Animation(texture, 0.3f));
	animations[BACK_WALK]->SetPart(10, 11, true);
}

void Player::DoAction()
{
	if (KEY_DOWN(VK_SHIFT))
	{
		Vector2 pos = { center.x, center.y + (size.y * 0.5f) };

		map->AttackMap(pos + CAM->Pos());
	}
}

void Player::SetAnimation(State value)
{
	if (state != value)
	{
		state = value;
		animations[state]->Play();
	}
}