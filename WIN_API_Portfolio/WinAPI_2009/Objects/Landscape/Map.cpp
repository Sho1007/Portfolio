#include "Framework.h"

void Map::Create()
{
	for (int h = 0; h < MAX_HEIGHT; ++h)
	{
		vector<vector<Tile*>> tileVectors;
		for (int i = 0; i < sizeY; ++i)
		{
			vector<Tile*> tileVector;
			for (int j = 0; j < sizeX; ++j)
			{
				Tile* tile = new Tile(baseFrame);
				tileVector.emplace_back(tile);
			}
			tileVectors.emplace_back(tileVector);
		}
		mapTile[h] = tileVectors;
	}
}

void Map::Destroy()
{
	for (auto tileVectors : mapTile)
	{
		for (vector<Tile*> tileVector : tileVectors.second)
		{
			for (Tile* tile : tileVector)
			{
				delete tile;
			}
			tileVector.clear();
		}
		tileVectors.second.clear();
	}
}

void Map::AddRow()
{
	if (sizeY >= MAX_SIZE)
		return;
	for (auto tileVectors : mapTile)
	{
		vector<Tile* > tileVector;
		for (int i = 0; i < sizeX; ++i)
		{
			Tile* tile = new Tile(baseFrame);
			tileVector.emplace_back(tile);
		}
		tileVectors.second.emplace_back(tileVector);
	}
	sizeY++;
}

void Map::AddCol()
{
	if (sizeX >= MAX_SIZE)
		return;
	for (auto tileVectors : mapTile)
	{
		for (vector<Tile*> tileVector : tileVectors.second)
		{
			Tile* tile = new Tile(baseFrame);
			tileVector.emplace_back(tile);
		}
	}
	sizeX++;
}

void Map::DelRow()
{
	if (sizeY < MIN_SIZE)
		return;
	for (auto tileVectors : mapTile)
	{
		for (Tile* tile : tileVectors.second[sizeY - 1])
		{
			delete tile;
		}
		tileVectors.second[sizeY - 1].clear();
		tileVectors.second.pop_back();
	}
	sizeY--;
}

void Map::DelCol()
{
	if (sizeX < MIN_SIZE)
		return;
	for (auto tileVectors : mapTile)
	{
		for (vector<Tile*> tileVector : tileVectors.second)
		{
			Tile* tile = *(tileVector.end());
			delete tile;
			tileVector.pop_back();
		}
	}
	sizeX--;
}

void Map::SetTile()
{
	for (auto tileVectors : mapTile)
	{
		float  width = mapRect.size.x / sizeX;

		float height = mapRect.size.y / sizeY;
		for (int i = 0; i < sizeY; ++i)
		{
			for (int j = 0; j < sizeX; ++j)
			{
				if (i == 0)
					tileVectors.second[i][j]->rect.center.y = mapRect.Top() + (height * 0.5f);
				else
					tileVectors.second[i][j]->rect.center.y = tileVectors.second[i - 1][j]->rect.center.y + height;
				if (j == 0)
					tileVectors.second[i][j]->rect.center.x = mapRect.Left() + (width * 0.5f);
				else
					tileVectors.second[i][j]->rect.center.x = tileVectors.second[i][j - 1]->rect.center.x + width;

				tileVectors.second[i][j]->rect.size = { width, height };
			}
		}
	}
}

void Map::SetRect(float left, float top, float right, float bottom)
{
	mapRect.SetRect(left, top, right, bottom);

	SetTile();
}

void Map::AddSize(float value)
{
	SetRect(mapRect.Left() - (value * 0.5f), mapRect.Top() - (value * 0.5f), mapRect.Right() + (value * 0.5f), mapRect.Bottom() + (value * 0.5f));
}

void Map::SubSize(float value)
{
	SetRect(mapRect.Left() + (value * 0.5f), mapRect.Top() + (value * 0.5f), mapRect.Right() - (value * 0.5f), mapRect.Bottom() - (value * 0.5f));
}

void Map::MoveCenter(Vector2 value)
{
	mapRect.center += value * 20.0f;

	SetTile();
}

void Map::SetDebug()
{
	if (debug)
		debug = false;
	else
		debug = true;
}

Map::Map(Texture* tileTexture, int sizeX, int sizeY, POINT baseFrame)
	: tileTexture(tileTexture), sizeX(sizeX), sizeY(sizeY), baseFrame(baseFrame)
{
	Create();
}

Map::~Map()
{
	Destroy();
}

void Map::Update()
{
}

void Map::Render()
{
	if (debug)
		oldBrush = (HBRUSH)SelectObject(Program::BackBuffer(), GetStockObject(NULL_BRUSH));
	for (auto tileVectors : mapTile)
	{
		for (vector<Tile*> tileVector : tileVectors.second)
		{
			for (Tile* tile : tileVector)
			{
				tileTexture->Render(&tile->rect, tile->frame);
				if (debug)
					Rectangle(Program::BackBuffer(), tile->rect.Left(), tile->rect.Top(), tile->rect.Right(), tile->rect.Bottom());
			}
		}
	}

	if (debug)
		SelectObject(Program::BackBuffer(), oldBrush);
}
