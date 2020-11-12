#include "Framework.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	Texture* texture = TEXTURE->Add(L"Textures/star_out.bmp", 400, 1264, SAMPLE_TILE_X, SAMPLE_TILE_Y, WHITE);
	map = new Map(texture, 30, 30, { 0, 7 });
	map->SetRect(-1000, -1000, 2000, 2000);
		
	CreateSampleTile();
	CreateMap();
}

MapToolScene::~MapToolScene()
{
}

void MapToolScene::Update()
{
	ClickSample();
	ClickMap();

	if (KEY_DOWN(VK_F1))
		Save();

	if (KEY_DOWN(VK_F2))
		Load();

	if (KEY_PRESS(VK_F10))
		map->AddSize(50.0f);
	if (KEY_PRESS(VK_F11))
		map->SubSize(50.0f);	
}

void MapToolScene::Render(HDC hdc)
{
	map->Render();
}

void MapToolScene::ClickSample()
{
	/*if (KEY_DOWN(VK_LBUTTON))
	{
		for (Tile sample : sampleTile)
		{
			if (sample.rect.IsCollision(mousePos))
			{
				curTile = sample.frame;
				return;
			}
		}
	}*/
}

void MapToolScene::ClickMap()
{
	/*if (KEY_PRESS(VK_LBUTTON))
	{
		for (Tile& map : mapTiles[nowH])
		{
			if (map.rect.IsCollision(mousePos))
			{
				map.frame = curTile;
				return;
			}
		}
	}*/
}

void MapToolScene::Save()
{
	//HANDLE file;
	//// 다음걸 또 저장할때 이전까지의 크기를 여기에 저장
	//DWORD write;

	//file = CreateFile(L"TextData/Tile.map", GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
	//	FILE_ATTRIBUTE_NORMAL, nullptr);
	//// LPCVOID
	//// void* -> void 포인터 (어떤 주소값도 다 가질 수 있다)
	//// UINT size = sizeof(mapTile)
	//UINT size = sizeof(Tile) * TILE_SIZE;
	//for (int i = 0; i < 4; ++i)
	//{
	//	WriteFile(file, mapTiles[i], size, &write, nullptr);
	//}
	//CloseHandle(file);
}

void MapToolScene::Load()
{
	/*HANDLE file;
	DWORD read;

	file = CreateFile(L"TextData/Tile.map", GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, nullptr);

	UINT size = sizeof(Tile) * TILE_SIZE;
	for(int i = 0; i < 4; ++i)
	{
		ReadFile(file, mapTiles[i], size, &read, nullptr);
	}

	CloseHandle(file);*/
}

void MapToolScene::CreateSampleTile()
{
	/*Vector2 startPos(CENTER_X + 200, 100);
	Vector2 size = tileTexture->GetSize();

	float interval = 2.0f;

	for (int y = 0; y < SAMPLE_TILE_Y; ++y)
	{
		for (int x = 0; x < SAMPLE_TILE_X; ++x)
		{
			int index = y * SAMPLE_TILE_X + x;
			
			Vector2 offset(x * (size.x + interval), y * (size.y + interval));

			sampleTile[index].frame = { x,y };
			sampleTile[index].rect = Rect(startPos + offset, size);
		}
	}*/
}

void MapToolScene::CreateMap()
{
	/*Vector2 startPos(100, 100);
	Vector2 size = tileTexture->GetSize();

	for (int i = 0; i < 4; ++i)
	{
		for (int y = 0; y < TILE_Y; ++y)
		{
			for (int x = 0; x < TILE_X; ++x)
			{
				int index = y * TILE_X + x;

				Vector2 offset(x * size.x, y * size.y);
				mapTiles[i][index].rect = Rect(startPos + offset, size);
				if (i != 0)
					mapTiles[i][index].frame = { 0, 5 };
			}
		}
	}*/
	
}
