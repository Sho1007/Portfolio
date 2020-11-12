#include "Framework.h"

Angie::Angie()
	: state(IDLE), speed(100), jumpPower(0.0f), gravity(980.0f)
{
	LoadXML("Textures/Angie/", "Angie.xml");
	animations[ATTACK]->SetEndEvent(bind(&Angie::SetIdle, this));
	size = { 100, 200 };
	center = { CENTER_X, 0 };

	animations[state]->Play();

	mountain = TEXTURE->Find(L"Textures/map_land.bmp");

	shell = new Shell();

	brush = CreateSolidBrush(MAGENTA);
	pen = CreatePen(PS_SOLID, 1, MAGENTA);
}

Angie::~Angie()
{
	delete shell;
	DeleteObject(brush);
	DeleteObject(pen);
}

void Angie::Update()
{
	animations[state]->Update();
	Move();
	Attack();
	Jump();
	shell->Update();
}

void Angie::Render()
{
	RECT rect = animations[state]->GetRectFrame();
	size.x = rect.right;
	size.y = rect.bottom;
	size *= 0.5f;

	Rect temp;
	temp.size = size;
	temp.center = center - CAM->Pos();

	texture->Render(&temp, rect);

	shell->Render(Program::BackBuffer());
}

void Angie::LoadXML(string path, string file)
{
	XmlDocument* document = new XmlDocument();
	document->LoadFile((path + file).c_str());

	XmlElement* textureAtlas = document->FirstChildElement();
	wstring filePath = ToWString(path + textureAtlas->Attribute("imagePath"));

	texture = TEXTURE->Add(filePath, textureAtlas->IntAttribute("width"), textureAtlas->IntAttribute("height"));

	XmlElement* action = textureAtlas->FirstChildElement();

	for (; action != nullptr; action = action->NextSiblingElement())
	{
		Animation* animation = new Animation(texture);

		bool loop = action->IntAttribute("loop");
		bool pingpong = action->IntAttribute("pingpong");

		animation->Loop(loop);
		animation->PingPong(pingpong);

		XmlElement* sprite = action->FirstChildElement();

		for (; sprite != nullptr; sprite = sprite->NextSiblingElement())
		{
			RECT rect;
			rect.left = sprite->IntAttribute("x");
			rect.top = sprite->IntAttribute("y");
			rect.right = sprite->IntAttribute("w");
			rect.bottom = sprite->IntAttribute("h");

			animation->SetRectFrame(rect);
		}
		animations.emplace_back(animation);
	}
}

void Angie::SetAnimation(State state)
{
	if (this->state != state)
	{
		this->state = state;
		animations[state]->Play();
	}
}

void Angie::SetIdle()
{
	SetAnimation(IDLE);
}

float Angie::GetMountainY(Vector2 pos)
{
	if (mountain == nullptr)
		return WIN_HEIGHT;

	int x = (pos.x / WIN_WIDTH) * mountain->GetSize().x;
	int y = (pos.y / WIN_HEIGHT) * mountain->GetSize().y;

	for (int i = y; i < WIN_HEIGHT; ++i)
	{
		COLORREF color = GetPixel(mountain->GetMemDC(), x, i);

		float height = WIN_HEIGHT * i / mountain->GetSize().y;

		if (color != MAGENTA)
			return height;
	}
	return WIN_HEIGHT;
}

void Angie::Move()
{
	if (KEY_PRESS(VK_RIGHT))
	{
		center.x += speed * DELTA;
		SetAnimation(RUN);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		center.x -= speed * DELTA;
		SetAnimation(RUN);
	}

	if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT))
	{
		SetAnimation(IDLE);
	}
}

void Angie::Attack()
{
	if (KEY_DOWN(VK_SPACE))
	{
		SetAnimation(ATTACK);

		shell->Fire(center, PI/4, 5000);
	}

	float mountainY = GetMountainY(shell->GetBall()->center);

	if (shell->IsFire() && mountainY < shell->GetBall()->center.y)
	{
		shell->SetFire(false);

		HDC hdc = mountain->GetMemDC();

		SelectObject(hdc, brush);
		SelectObject(hdc, pen);

		float radius = 50.0f;

		int left = shell->GetBall()->Left() - radius;
		int top = shell->GetBall()->Top() - radius; 
		int right = shell->GetBall()->Right() + radius;
		int bottom = shell->GetBall()->Bottom() + radius;

		Ellipse(hdc, left, top, right, bottom);
	}
}

void Angie::Jump()
{
	if (KEY_DOWN(VK_UP))
	{
		jumpPower = 800.0f;
	}
	jumpPower -= gravity * DELTA;
	center.y = jumpPower * DELTA;
	float landY = GetMountainY(center) - Half().y + 30.0f;

	if (center.y > landY)
	{
		center.y = landY;
		jumpPower = 0.0f;
	}
}
