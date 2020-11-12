#include "Framework.h"

void Landscape::CreateBG()
{
	Texture* skyTexture = TEXTURE->Add(L"Textures/background.bmp", 740, 164);
	sky[0] = new ImageRect(skyTexture);
	sky[0]->SetRect(0, 0, WIN_WIDTH, WIN_HEIGHT);
	sky[1] = new ImageRect(skyTexture);
	sky[1]->SetRect(WIN_WIDTH, 0, WIN_WIDTH * 2, WIN_HEIGHT);
}

void Landscape::CreateLand()
{
	Texture* landTexture = TEXTURE->Add(L"Textures/land.bmp", 740, 299);

	float landY = WIN_HEIGHT - landTexture->GetSize().y * 0.1f;

	for (UINT i = 0; i < LAND; ++i)
	{
		ImageRect* land = new ImageRect(landTexture);

		float interval = Random(50.0f, 200.0f);

		float landX;
		if (i != 0)
		{
			landX = lands[i - 1]->center.x + land->size.x + interval;
		}
		if (i == 0)
		{
			landX = land->Half().x;
		}

		land->center = { landX, landY };

		lands.emplace_back(land);
	}
}

void Landscape::CreateBlock()
{
	Texture* texture = TEXTURE->Add(L"Textures/marioBlocks.bmp", 460, 92, 5, 1);

	for (UINT i = 0; i < BLOCK; ++i)
	{
		ImageRect* block = new ImageRect(texture, { 3, 0 });
		block->size = { 60.0f, 60.0f };
		block->center.x = 300 + block->size.x * i;
		block->center.y = 400;
		blocks.emplace_back(block);
	}

	Texture* expTexture = TEXTURE->Add(L"Textures/exp.bmp", 512, 512, 4, 4);
	EffectManager::Get()->Add("exp", expTexture, 10);
}

Landscape::Landscape()
	: skySpeed(60), landSpeed(100)

{
	CreateBG();
	CreateLand();
	CreateBlock();
}

Landscape::~Landscape()
{
	for (ImageRect* s : sky)
		delete s;

	for (ImageRect* land : lands)
	{
		delete land;
	}

	for (ImageRect* block : blocks)
	{
		delete block;
	}
}

void Landscape::Update()
{
	EffectManager::Get()->Update();
	for (int i = 0; i < 2; i++)
	{
		sky[i]->center.x -= skySpeed * DELTA;

		if (sky[i]->Right() <= 0)
			sky[i]->center.x += WIN_WIDTH * 2.0f;
	}

	for (UINT i = 0; i < lands.size(); ++i)
	{
		lands[i]->center.x -= landSpeed * DELTA;

		if (lands[i]->Right() <= 0)
		{
			int lastIndex = i - 1;
			lastIndex = lastIndex < 0 ? lands.size() - 1 : lastIndex;	

			float interval = Random(50.0f, 200.0f) + lands[i]->Half().x;

			lands[i]->center.x = lands[lastIndex]->Right() + interval;
		}
	}
}

void Landscape::Render()
{
	for (ImageRect* s : sky)
		s->Render();

	for (ImageRect* land : lands)
	{
		land->Render();
	}

	for (ImageRect* block : blocks)
	{
		block->Render();
	}

	EffectManager::Get()->Render();
}

Direction Landscape::PushCollision(Rect* rect)
{
	for (ImageRect* land : lands)
	{
		Rect temp;
		if (land->IsRectCollision(&temp, rect))
		{
			if (temp.size.x > temp.size.y)
			{
				if (land->center.y < rect->center.y)
				{
					rect->center.y += temp.size.y;
					return Direction::DOWN;
				}
				else
				{
					rect->center.y -= temp.size.y;
					return Direction::UP;
				}
			}
			else
			{
				if (land->center.x < rect->center.x)
				{
					rect->center.x += temp.size.x;
					return Direction::RIGHT;
				}
				else
				{
					rect->center.x -= temp.size.x;
					return Direction::DOWN;
				}
			}
		}
	}

	for (ImageRect* block : blocks)
	{
		Rect temp;
		if (block->IsRectCollision(&temp, rect))
		{
			if (temp.size.x > temp.size.y)
			{
				if (block->center.y < rect->center.y)
				{
					if (mario->GetJumpForce() > 0)
						block->isActive = false;
					rect->center.y += temp.size.y;
					EffectManager::Get()->Play("exp", block->center);
					
					return Direction::DOWN;
				}
				else
				{
					rect->center.y -= temp.size.y;
					return Direction::UP;
				}
			}
			else
			{
				if (block->center.x < rect->center.x)
				{
					rect->center.x += temp.size.x;
					return Direction::RIGHT;
				}
				else
				{
					rect->center.x -= temp.size.x;
					return Direction::DOWN;
				}
			}
		}
	}
	return Direction::NONE;
}
