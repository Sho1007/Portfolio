#include "Framework.h"
#include "GameScene.h"

void GameScene::Create()
{
	bg = TEXTURE->Add(L"Textures/dark.bmp", 1264, 741);
	Texture* texture = TEXTURE->Add(L"Textures/star_out.bmp", 400, 1264, 25, 79, WHITE);
	map = new Map(texture, 30, 30, { 0, 5 });
	map->SetLayerFrame(0, { 0, 7 });
	map->SetRect(0, 0, 2250, 2250);
	map->MoveCenter({ CENTER_X, CENTER_Y });

	player = new Player();
	player->center = map->GetRect()->center;
	player->SetMap(map);

	CAM->SetPos({ 0, 0 });
	CAM->GetMapRect()->center = map->GetRect()->center;
	CAM->GetMapRect()->size = map->GetRect()->size;
	//CAM->SetTarget(player);
}

void GameScene::Destroy()
{
	delete map;
	delete player;
}

GameScene::GameScene()
{
	Create();
}

GameScene::~GameScene()
{
	Destroy();
}

void GameScene::Update()
{
	map->Update();
	player->Update();
}

void GameScene::Render(HDC hdc)
{
	map->Render();
	player->Redner();
	int alpha;
	int hour = GM->GetHour();
	if (hour < 12)
	{
		alpha = 230 - (20 * hour);
	}
	else if (hour < 16)
	{
		alpha = 0.0f;
	}
	else
	{
		alpha = 13 * (hour - 6);
	}
	bg->Render(CAM->GetMapRect(), alpha);
}
