#include "Framework.h"

void EnemyManager::Create()
{
	for (int i = 0; i < 50; ++i)
	{
		enemies.emplace_back(new Enemy());
		enemies[i]->SetMap(map);
		enemies[i]->SetTarget(player);
	}
	
	spawnTime = 3.0f;
	spawnTimeNow = 0.0f;
}

void EnemyManager::Destroy()
{
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
}

EnemyManager::EnemyManager(Rect* player, Map* map)
	: player(player), map(map)
{
	Create();
}

EnemyManager::~EnemyManager()
{
	Destroy();
}

void EnemyManager::Update()
{
	sort(enemies.begin(), enemies.end(), Enemy::Compare);
	if (spawnTimeNow > 0.0f)
		spawnTimeNow -= DELTA;
	if (spawnTimeNow <= 0.0f)
	{
		spawnTimeNow = spawnTime;
		SpawnEnemy();
	}
	for (Enemy* enemy : enemies)
	{
		enemy->Update();
		for (Enemy* enemy2 : enemies)
		{
			if (enemy2->isActive)
				CheckCollision(enemy, enemy2);
		}
	}
}

void EnemyManager::Render()
{
	for (Enemy* enemy : enemies)
	{
		enemy->Render();
	}
}

void EnemyManager::SpawnEnemy()
{
	for (Enemy* enemy : enemies)
	{
		if (!enemy->isActive)
		{
			enemy->SetSpawn({ CENTER_X, 0 });
			break;
		}
	}
}

void EnemyManager::CheckCollision(Enemy* rc1, Enemy* rc2)
{
	Rect rc;
	if (rc1->colRect.IsRectCollision(&rc, &rc2->colRect))
	{
		if (rc1->center.x > rc2->center.x)
		{
			rc1->center.x += rc.size.x *  DELTA;
			rc2->center.x -= rc.size.x *  DELTA;
		}
		else
		{
			rc1->center.x -= rc.size.x *  DELTA;
			rc2->center.x += rc.size.x *  DELTA;
		}

		if (rc1->center.y > rc2->center.y)
		{
			rc1->center.y += rc.size.y * DELTA;
			rc2->center.y -= rc.size.y * DELTA;
		}
		else
		{
			rc1->center.y -= rc.size.y * DELTA;
			rc2->center.y += rc.size.y * DELTA;
		}
	}
}