#include "Framework.h"

void HWDragonEnemyManager::Create()
{
	bossCreate = false;
	respawnDelay = 10.0f;
	respawnTime = 0.0f;

	for (UINT i = 0; i < POOL_COUNT; ++i)
	{
		enemies.emplace_back(new HWDragonEnemy);
		enemies.back()->isActive = false;
		enemies.back()->SetBM(bm);
		enemies.back()->SetPlayer(player);
	}
}

void HWDragonEnemyManager::Destroy()
{
	for (HWDragonEnemy* enemy : enemies)
	{
		delete enemy;
	}
}

HWDragonEnemyManager::HWDragonEnemyManager()
{
}

HWDragonEnemyManager::~HWDragonEnemyManager()
{
	Destroy();
}

void HWDragonEnemyManager::Update()
{
	if (!bossCreate && Timer::Get()->GetRunTime() > 20.0f)
	{
		bossCreate = true;
		for (HWDragonEnemy* enemy : enemies)
		{
			if (!enemy->isActive)
			{
				enemy->CreateBoss();
				enemy->isActive = true;
				break;
			}

		}
	}
	if (respawnTime > 0.0f)
	{
		respawnTime -= DELTA;
	}

	if (respawnTime <= 0.0f)
	{
		respawnTime = respawnDelay;
		UINT random = Random(0, 3);
		for (HWDragonEnemy* enemy : enemies)
		{
			if (!enemy->isActive)
			{
				enemy->Create(random);
				enemy->isActive = true;
				break;
			}
				
		}
	}
	for (HWDragonEnemy* enemy : enemies)
	{
		if (enemy->isActive)
		{
			enemy->Update();
			bm->IsCollision("player", enemy);
			if (enemy->GetHp() <= 0)
			{
				if (enemy->GetIsBoss())
				{
					MessageBox(hWnd, L"GameClear", L"Alram", MB_OK);
					PostQuitMessage(0);
				}
				enemy->isActive = false;
				player->GetPowerUp();
			}
				
		}
			

	}
}

void HWDragonEnemyManager::Render()
{
	for (HWDragonEnemy* enemy : enemies)
	{
		if (enemy->isActive)
			enemy->Render();
	}
}
