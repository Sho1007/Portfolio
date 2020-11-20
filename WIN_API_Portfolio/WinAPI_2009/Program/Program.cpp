#include "Framework.h"
#include "Scenes/CameraScene.h"
#include "Scenes/MapToolScene.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"

HDC Program::backBuffer = nullptr;

Program::Program()
{
	DataManager::Get();
	CreateBackBuffer();

	SetBkMode(backBuffer, TRANSPARENT);

	srand((unsigned)time(NULL));

	SCENE->Add("start", new StartScene());
	SCENE->Add("game", new GameScene());
	SCENE->Add("tool", new MapToolScene());

	SCENE->ChangeScene("start");
	
}

Program::~Program()
{
	DeleteObject(hBitmap);
	DeleteDC(backBuffer);
}

void Program::Update()
{
	Control::Get()->Update();
	Timer::Get()->Update();

	SCENE->Update();
	CAM->Update();
	GM->Update();
}

void Program::Render(HDC hdc)
{
	PatBlt(backBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS);

	SCENE->Render(backBuffer);

	if (GM->IsDebug())
		Timer::Get()->Render(backBuffer);

	GM->Render(backBuffer);

	BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		backBuffer, 0, 0, SRCCOPY);
}

void Program::CreateBackBuffer()
{
	HDC hdc = GetDC(hWnd);

	backBuffer = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);

	SelectObject(backBuffer, hBitmap);

	ReleaseDC(hWnd, hdc);
}
