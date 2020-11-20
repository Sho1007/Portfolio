#include "Framework.h"

void Enemy::CreateActions()
{
	//	FRONT
	animations.emplace_back(new Animation(texture));
	animations[FRONT]->SetPart(0, 0);

	//	FRONT_WALK
	animations.emplace_back(new Animation(texture));
	animations[FRONT_WALK]->SetPart(0, 6, true);

	//	FRONT_ATTACK
	animations.emplace_back(new Animation(texture));
	animations[FRONT_ATTACK]->SetPart(28, 31);
	animations[FRONT_ATTACK]->SetEndEvent(bind(&Enemy::SetIdle, this));


	//	LEFT
	animations.emplace_back(new Animation(texture));
	animations[LEFT]->SetPart(7, 7);

	//	LEFT_WALK
	animations.emplace_back(new Animation(texture));
	animations[LEFT_WALK]->SetPart(7, 13, true);

	//	LEFT_ATTACK
	animations.emplace_back(new Animation(texture));
	animations[LEFT_ATTACK]->SetPart(32, 35);
	animations[LEFT_ATTACK]->SetEndEvent(bind(&Enemy::SetIdle, this));


	//	RIGHT
	animations.emplace_back(new Animation(texture));
	animations[RIGHT]->SetPart(14, 14);

	//	RIGHT_WALK
	animations.emplace_back(new Animation(texture));
	animations[RIGHT_WALK]->SetPart(14, 20, true);

	//	RIGHT_ATTACK
	animations.emplace_back(new Animation(texture));
	animations[RIGHT_ATTACK]->SetPart(36, 39);
	animations[RIGHT_ATTACK]->SetEndEvent(bind(&Enemy::SetIdle, this));


	//	BACK
	animations.emplace_back(new Animation(texture));
	animations[BACK]->SetPart(21, 21);

	//	BACK_WALK
	animations.emplace_back(new Animation(texture));
	animations[BACK_WALK]->SetPart(21, 27, true);

	//	BACK_ATTACK
	animations.emplace_back(new Animation(texture));
	animations[BACK_ATTACK]->SetPart(40, 43);
	animations[BACK_ATTACK]->SetEndEvent(bind(&Enemy::SetIdle, this));
}

void Enemy::SetIdle()
{
	switch (state)
	{
	case FRONT_WALK:
	case FRONT_ATTACK :
		SetAnimation(FRONT);
		break;
	case LEFT_WALK:
	case LEFT_ATTACK:
		SetAnimation(LEFT);
		break;
	case RIGHT_WALK:
	case RIGHT_ATTACK:
		SetAnimation(RIGHT);
		break;
	case BACK_WALK:
	case BACK_ATTACK:
		SetAnimation(BACK);
		break;
	}
}

void Enemy::SetAnimation(State value)
{
	if (state != value)
	{
		state = value;
		animations[state]->Play();
	}
}

void Enemy::Create()
{
	state = FRONT;
	texture = TEXTURE->Add(L"Textures/zombie.bmp", 448, 512, 7, 8);
	speed = 150.0f;
	attack = 50.0f;
	atkCool = 3.0f;
	atkCoolNow = 0.0f;
	isActive = false;
	

	CreateActions();
	animations[state]->Play();

	center = { CENTER_X, CENTER_Y };
	size = { 150, 150 };
	colRect.size.x = size.x * 0.25f;
	colRect.size.y = size.y * 0.25f;
	toward.size = { size.x * 0.5f, size.y * 0.5f };

	Texture* back = TEXTURE->Add(L"Textures/hpBarTop.bmp", 53, 5);
	Texture* front = TEXTURE->Add(L"Textures/hpBarBottom.bmp", 53, 5);
	hpBar = new HpBar(back, front, 100);
	hpBar->SetTarget(this);
	hpBar->size = { size.x * 0.5f, this->size.y * 0.1f };
	hpBar->SetOffset({ 0, Half().y });
}

void Enemy::Destroy()
{
	for (Animation* animation : animations)
	{
		delete animation;
	}
	delete hpBar;
}

void Enemy::SetSpawn(Vector2 pos)
{
	isActive = true;
	center = pos;
	hpBar->SetHp(100.0f);
}

void Enemy::Update()
{
	if (!isActive)
		return;

	colRect.center = { center.x, center.y + size.y * 0.3f};
	hpBar->Update();
	if (atkCoolNow > 0.0f)
		atkCoolNow -= DELTA;

	animations[state]->Update();

	dir = target->center - center;
	dir += CAM->Pos();
	float dis = dir.Length();
	if (dis >= 1.0f)
		dir.Normalize();
	toward.center = { center.x, center.y + size.y * 0.2f };
	toward.center += dir * 30.0f;
	
	if (dis >= 70.0f)
	{
		POINT frame = map->GetFrame(toward.center);
		if (frame.x == 4 && frame.y == 11)
		{
			
		}
		else
		{
			center += dir * speed * DELTA;
		}
			
		if (abs(dir.x) >= abs(dir.y))
		{
			if (dir.x < 0)
			{
				SetAnimation(RIGHT_WALK);
			}
			else if (dir.x > 0)
			{
				SetAnimation(LEFT_WALK);
			}
		}
		else
		{
			if (dir.y > 0)
			{
				SetAnimation(FRONT_WALK);
			}
			else if (dir.y < 0)
			{
				SetAnimation(BACK_WALK);
			}
		}
		
		
	}
	else
	{
		if (state == RIGHT_WALK
			|| state == LEFT_WALK
			|| state == FRONT_WALK
			|| state == BACK_WALK)
			SetIdle();
		if (atkCoolNow <= 0.0f)
		{
			atkCoolNow = atkCool;
			if (dir.x < 0)
			{
				SetAnimation(RIGHT_ATTACK);
			}
			else if (dir.x > 0)
			{
				SetAnimation(LEFT_ATTACK);
			}
			else if (dir.y > 0)
			{
				SetAnimation(FRONT_ATTACK);
			}
			else if (dir.y < 0)
			{
				SetAnimation(BACK_ATTACK);
			}
		}
	}
}

void Enemy::Render()
{
	if (!isActive)
		return;
	//Rectangle(Program::BackBuffer(), colRect.Left() - CAM->Pos().x, colRect.Top() - CAM->Pos().y, colRect.Right() - CAM->Pos().x, colRect.Bottom() - CAM->Pos().y);
	ImageRect::CamRender(animations[state]->GetFrame());
	//Rectangle(Program::BackBuffer(), toward.Left() - CAM->Pos().x, toward.Top() - CAM->Pos().y, toward.Right() - CAM->Pos().x, toward.Bottom() - CAM->Pos().y);
	//hpBar->Render();
}

Enemy::Enemy()
{
	Create();
}

Enemy::~Enemy()
{
	Destroy();
}

int Enemy::Compare(Enemy* e1, Enemy* e2)
{
	if (e1->center.y < e2->center.y)
		return 1;
	return 0;
}
