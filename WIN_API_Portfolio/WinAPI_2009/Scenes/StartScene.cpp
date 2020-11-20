#include "Framework.h"
#include "StartScene.h"

StartScene::StartScene()
{
	Create();
}

StartScene::~StartScene()
{
	Destroy();
}

void StartScene::Create()
{
	bg = TEXTURE->Add(L"Textures/StartBG.bmp", 937, 606);
	Texture* up = TEXTURE->Add(L"Textures/SignBtn1.bmp", 100, 50);
	Texture* over = TEXTURE->Add(L"Textures/SignBtn2.bmp", 100, 50);
	Texture* down = TEXTURE->Add(L"Textures/SignBtn3.bmp", 100, 50);

	startBtn = new Button("START", up, over, down);
	startBtn->center = { CENTER_X, WIN_HEIGHT * 0.6f };
	startBtn->size = { 250, 100 };
	startBtn->SetEvent(bind(&StartScene::StartAction, this));

	mapToolBtn = new Button("TOOL", up, over, down);
	mapToolBtn->center = { CENTER_X, WIN_HEIGHT * 0.7f };
	mapToolBtn->size = { 250, 100 };
	mapToolBtn->SetEvent(bind(&StartScene::ToolAction, this));

	exitBtn = new Button("EXIT", up, over, down);
	exitBtn->center = { CENTER_X, WIN_HEIGHT * 0.8f };
	exitBtn->size = { 250, 100 };
	exitBtn->SetEvent(bind(&StartScene::Exit, this));
}

void StartScene::Destroy()
{
	delete startBtn;
	delete mapToolBtn;
	delete exitBtn;
}

void StartScene::StartAction()
{
	GM->SetPlay(true);
	SCENE->ChangeScene("game");
}

void StartScene::ToolAction()
{
	SCENE->ChangeScene("tool");
}

void StartScene::Exit()
{
	PostQuitMessage(0);
}


void StartScene::Update()
{
	startBtn->Update();
	mapToolBtn->Update();
	exitBtn->Update();
}

void StartScene::Render(HDC hdc)
{
	Rect temp = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	bg->Render(&temp);
	startBtn->Render();
	mapToolBtn->Render();
	exitBtn->Render();
}
