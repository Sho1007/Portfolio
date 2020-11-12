#include "Framework.h"
#include "HWBlockManager.h"

HWBlockManager::HWBlockManager()
	: coinCount(4)
{
	blockTexture = TEXTURE->Add(L"Textures/marioBlocks.bmp", 460, 92, 5, 1);
	ImageRect* rect = new ImageRect(blockTexture, { 3, 0 });
	rect->size = { 60.0f, 60.0f };
	rect->center = { WIN_WIDTH - rect->size.x, 270 };
	blocks.emplace_back(rect);
	rect = new ImageRect(blockTexture, { 3, 0 });
	rect->size = { 60.0f, 60.0f };
	rect->center = { WIN_WIDTH - rect->size.x * 2, 270 };
	blocks.emplace_back(rect);
	rect = new ImageRect(blockTexture, { 4, 0 });
	rect->size = { 60.0f, 60.0f };
	rect->center = { WIN_WIDTH - rect->size.x * 3, 270 };
	blocks.emplace_back(rect);

	rect = new ImageRect(blockTexture, { 2, 0 });
	rect->size = { 60.0f, 60.0f };
	rect->center = { WIN_WIDTH - rect->size.x * 3, 50 };
	blocks.emplace_back(rect);
	blockSpeed = 100.0f;
}

HWBlockManager::~HWBlockManager()
{
	for (auto block : blocks)
	{
		delete block;
	}
}

void HWBlockManager::Update()
{
	for (auto block : blocks)
	{
		block->center.x -= blockSpeed * DELTA;
	}
}

void HWBlockManager::Render()
{
	for (auto block : blocks)
	{
		block->Render();
	}
}

Direction HWBlockManager::PushCollision(Rect* rect)
{
	POINT point;
	vector<ImageRect*>::iterator iter = blocks.begin();
	for (; iter != blocks.end(); ++iter)
	{
		Rect temp;
		if ((*iter)->IsRectCollision(&temp, rect))
		{
			if (temp.size.x > temp.size.y)
			{
				if ((*iter)->center.y < rect->center.y)
				{
					point = (*iter)->GetFrame();
					rect->center.y += temp.size.y;
					if (point.x == 3)
					{
						AUDIO->Play("blockBreak");
						blocks.erase(iter);
					}
					else if (point.x == 4 || point.x == 0)
					{
						AUDIO->Play("hitBlock");
					}
					else if (point.x == 2)
					{
						if (coinCount > 0) {
							AUDIO->Play("getCoin");
							coinCount--;
						}
						if (coinCount == 0)
							(*iter)->SetTexture(blockTexture, { 0, 0 });
						
					}
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
				if ((*iter)->center.x < rect->center.x)
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
	return Direction();
}
