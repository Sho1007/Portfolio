#include "Framework.h"

Mario::Mario()
	: state(IDLE), speed(200), gravity(980.0f), jumpForce(0), isJump(true), colDir(Direction::NONE)
{
	texture = TEXTURE->Add(L"Textures/mario.bmp", 512, 328, 8, 4);

	center = { CENTER_X, CENTER_Y };
	size = texture->GetSize();

	CreateActions();
	animations[IDLE]->Play();

	Timer::Get()->SetLockFPS(60);

	
}

Mario::~Mario()
{
	for (Animation* animation : animations)
		delete animation;
}

void Mario::Update()
{
	Move();
	Jump();
	Attack();

	animations[state]->Update();
}

void Mario::Render()
{
	ImageRect::Render(animations[state]->GetFrame());
}

void Mario::Move()
{
	if (KEY_PRESS(VK_RIGHT))
	{
		center.x += speed * DELTA;		
		isRight = true;

		if(!isJump)
			SetAnimation(R_WALK);
	}

	if (KEY_PRESS(VK_LEFT))
	{
		center.x -= speed * DELTA;		
		isRight = false;
		if (!isJump)
			SetAnimation(L_WALK);
	}

	if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT))
	{
		if(!isJump)
			SetAnimation(IDLE);
	}
}

void Mario::Jump()
{
	if (!isJump && KEY_DOWN(VK_UP))
	{
		AUDIO->Play("jump");
		isJump = true;
		jumpForce = F;
		
		if (isRight)
			SetAnimation(R_JUMPUP);
		else
			SetAnimation(L_JUMPUP);
	}

	jumpForce -= gravity * DELTA;
	center.y -= jumpForce * DELTA;

	colDir = bm->PushCollision(this);
	if (colDir == Direction::UP)
	{
		if (isJump)
			SetAnimation(IDLE);

		isJump = false;
		jumpForce = 0.0f;
	}
	else if (colDir == Direction::DOWN)
	{
		jumpForce = 0.0f;
	}


	Direction dir = landscape->PushCollision(this);

	switch (dir)
	{
	case GameMath::Direction::UP :
		if (jumpForce < 0)	// 다시 보기 중요
		{
			if (isJump)
				SetAnimation(IDLE);

			isJump = false;
			jumpForce = 0.0f;
		}
		break;
	case GameMath::Direction::DOWN :
		if (jumpForce >0)	// 다시 보기 중요
			jumpForce = 0.0f;
		break;
	}


	if (jumpForce < 0)
	{
		if (isRight)
			SetAnimation(R_JUMPDOWN);
		else
			SetAnimation(L_JUMPDOWN);
	}
}

void Mario::Attack()
{
	if (KEY_DOWN(VK_SPACE))
	{
		if (isRight)
			SetAnimation(R_ATTACK);
		else
			SetAnimation(L_ATTACK);
	}
}

void Mario::CreateActions()
{
	//Idle
	animations.emplace_back(new Animation(texture));
	int arr[] = { 25, 26, 29 };
	animations[IDLE]->SetArray(arr, 3, true, true);	

	//R_Walk
	animations.emplace_back(new Animation(texture));		
	animations[R_WALK]->SetPart(0, 1, true);

	//L_Walk
	animations.emplace_back(new Animation(texture));
	animations[L_WALK]->SetPart(4, 5, true);

	//R_JUMPUP
	animations.emplace_back(new Animation(texture));
	animations[R_JUMPUP]->SetPart(2, 2, true);

	//L_JUMPUP
	animations.emplace_back(new Animation(texture));
	animations[L_JUMPUP]->SetPart(6, 6, true);

	//R_JUMPDOWN
	animations.emplace_back(new Animation(texture));
	animations[R_JUMPDOWN]->SetPart(3, 3, true);

	//L_JUMPDOWN
	animations.emplace_back(new Animation(texture));
	animations[L_JUMPDOWN]->SetPart(7, 7, true);

	//R_ATTACK
	animations.emplace_back(new Animation(texture));
	animations[R_ATTACK]->SetPart(16, 18, false);
	animations[R_ATTACK]->SetEndEvent(bind(&Mario::SetIdle, this));

	//L_ATTACK
	animations.emplace_back(new Animation(texture));
	animations[L_ATTACK]->SetPart(20, 22, false);
	animations[L_ATTACK]->SetEndEvent(bind(&Mario::SetIdle, this));
}

void Mario::SetAnimation(ActionState value)
{
	if (state != value)
	{
		state = value;
		animations[state]->Play();
	}
}

void Mario::SetIdle()
{
	SetAnimation(IDLE);
}
