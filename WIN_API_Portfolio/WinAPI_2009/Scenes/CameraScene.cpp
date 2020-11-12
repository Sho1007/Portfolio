#include "Framework.h"
#include "CameraScene.h"

CameraScene::CameraScene()
{
	mapSky = new ImageRect(TEXTURE->Add(L"Textures/map_sky.bmp", 1664, 488));
	mapBG = new ImageRect(TEXTURE->Add(L"Textures/map_bg.bmp", 1664, 409));
	mapLand = new ImageRect(TEXTURE->Add(L"Textures/map_land.bmp", 1448, 237));

	mapSky->size *= 2.0f;
	mapBG->size *= 2.0f;
	mapLand->size *= 2.0f;

	mapSky->center += mapSky->Half();
	mapBG->center += mapBG->Half();
	mapLand->center += mapLand->Half();

	mapSky->center.y -= mapSky->size.y - mapLand->size.y;
	mapBG->center.y -= mapBG->size.y - mapLand->size.y;

	angie = new Angie();

	CAM->SetPos({0, 0});
	CAM->GetMapRect()->center = mapSky->center;
	CAM->GetMapRect()->size = mapSky->size;
	CAM->SetTarget(angie);
}

CameraScene::~CameraScene()
{
	delete mapSky;
	delete mapBG;
	delete mapLand;

	delete angie;
}

void CameraScene::Update()
{
	angie->Update();
}

void CameraScene::Render(HDC hdc)
{
	mapSky->CamRender();
	mapBG->CamRender();
	mapLand->CamRender();
	angie->Render();
}
