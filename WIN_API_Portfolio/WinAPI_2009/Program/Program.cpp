#include "Framework.h"
#include "Scenes/CameraScene.h"
#include "Scenes/MapToolScene.h"

HDC Program::backBuffer = nullptr;

Program::Program()
{
	DataManager::Get();
	CreateBackBuffer();

	SetBkMode(backBuffer, TRANSPARENT);

	srand((unsigned)time(NULL));

	/*SCENE->Add("start", new StartScene());
	SCENE->Add("game", new ShootingScene());
	SCENE->Add("select", new ShootingSelectScene());*/

	/*SCENE->Add("start", new HWDragonStartScene());
	SCENE->Add("game", new HWShootingScene());

	SCENE->ChangeScene("start");

	AUDIO->Add("BG1", "Sounds/dragonBG1.mp3", true);
	AUDIO->Add("BG2", "Sounds/start.mp3", true);*/

	//SCENE->Add("start", new PixelCollisionScene());
	//SCENE->Add("start", new AlphaScene());
	//SCENE->Add("start", new AnimationScene());
	//SCENE->Add("start", new CameraScene());
	SCENE->Add("start", new MapToolScene());

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
}

void Program::Render(HDC hdc)
{
	PatBlt(backBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS);

	SCENE->Render(backBuffer);

	Timer::Get()->Render(backBuffer);

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
