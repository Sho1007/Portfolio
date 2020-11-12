#include "Framework.h"
#include "HWBird.h"

HWBird::HWBird()
	: state(IDLE), gravity(980.0f), jumpForce(0.0f), isJump(false)
{
	texture = TEXTURE->Add(L"Textures/mario.bmp", 512, 328, 8, 4);

	center = { CENTER_X, CENTER_Y };
	size = texture->GetSize();

	CreateActions();
	animations[IDLE]->Play();
}

HWBird::~HWBird()
{
	for (auto animation : animations)
	{
		delete animation;
	}
}

void HWBird::Update()
{
	Jump();

	animations[state]->Update();
}

void HWBird::Render()
{
	ImageRect::Render(animations[state]->GetFrame());
}

void HWBird::Jump()
{
	if (KEY_DOWN(VK_UP))
	{
		isJump = true;
		jumpForce = F;

		SetAnimation(JUMP);
	}

	jumpForce -= gravity * DELTA;
	center.y -= jumpForce * DELTA;

	if (jumpForce < 0.0f)
		SetAnimation(IDLE);


	if (Bottom() > WIN_HEIGHT)
	{
		MessageBox(hWnd, L"GameOver", L"Alram", MB_OK);
		PostQuitMessage(0); 
	}
}

void HWBird::CreateActions()
{
	//Idle
	animations.emplace_back(new Animation(texture));
	int arr[] = { 25, 26, 29 };
	animations[IDLE]->SetPart(16, 16, true);

	//R_JUMPUP
	animations.emplace_back(new Animation(texture));
	animations[JUMP]->SetPart(2, 2, true);
}

void HWBird::SetAnimation(ActionState value)
{
	if (state != value)
	{
		state = value;
		animations[state]->Play();
	}
}
