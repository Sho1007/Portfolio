#include "Framework.h"
#include "HWShootingScene.h"

HWShootingScene::HWShootingScene()
{
	Start();
}

HWShootingScene::~HWShootingScene()
{
	End();
}

void HWShootingScene::Start()
{
	AUDIO->Stop("BG2");
	AUDIO->Play("BG1");
	player = new HWDragonPlayer();
	landscape = new DragonLandscape();
	AUDIO->Add("shot", "Sounds/shot.wav");
	AUDIO->Add("enemyShot1", "Sounds/enemyShot1.wav");
	AUDIO->Add("enemyShot2", "Sounds/enemyShot2.wav");
	AUDIO->Add("enemyShot3", "Sounds/enemyShot3.wav");
	AUDIO->Add("exp", "Sounds/exp.wav");

	bm = new BulletManager();
	em = new HWDragonEnemyManager();
	em->SetBM(bm);
	em->SetPlayer(player);
	em->Create();
	player->SetBM(bm);
	
	Texture* bulletTexture = TEXTURE->Add(L"Textures/HWShoot/bullet1.bmp", 64, 35, 4, 1);
	bm->CreateBullet("player", bulletTexture, 50);
	Texture* enemyBulletTexture = TEXTURE->Add(L"Textures/HWShoot/enemyBullet.bmp", 15, 15);
	bm->CreateBullet("enemy", enemyBulletTexture, 100);
	CreateEffect();
}

void HWShootingScene::Update()
{
	landscape->Update();
	player->Update();
	em->Update();
	bm->Update();
	EFFECT->Update();
}

void HWShootingScene::Render(HDC hdc)
{
	landscape->Render();
	player->Render();
	em->Render();
	bm->Render();
	GameManager::Get()->Render(hdc);
	EFFECT->Render();
}

void HWShootingScene::End()
{
	delete player;
	delete landscape;
	delete bm;
	delete em;
}

void HWShootingScene::CreateEffect()
{
	Texture* texture = TEXTURE->Add(L"Textures/exp.bmp", 512, 512, 4, 4);
	EFFECT->Add("exp", texture, 30);
}