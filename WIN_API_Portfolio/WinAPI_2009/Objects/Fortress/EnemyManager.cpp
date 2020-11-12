#include "Framework.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
	: spawnTime(0), time(0)
{
	Texture* texture = TEXTURE->Add(L"Textures/ufo.bmp", 530, 32, 10, 1);

	for (int i = 0; i < POOL_COUNT; i++)
	{
		enemies.emplace_back(new Enemy(texture));
	}
}

EnemyManager::~EnemyManager()
{
	for (Enemy* enemy : enemies)
		delete enemy;
}

void EnemyManager::Update()
{
	time += DELTA;
	if (spawnTime < time)
	{
		CreateEnemy();
		time = 0.0f;
		spawnTime = Random(0.1f, 1.0f);
	}

	for (Enemy* enemy : enemies)
		enemy->Update();

	Collision();
}

void EnemyManager::Render()
{
	for (Enemy* enemy : enemies)
		enemy->Render();
}

void EnemyManager::Collision()
{
	for (Enemy* enemy : enemies)
	{
		if (!enemy->isActive)
			continue;

		bm->IsCollision("player", enemy);
	}
}

void EnemyManager::CreateEnemy()
{
	Vector2 pos(Random(0, WIN_WIDTH), 0);
	
	for (Enemy* enemy : enemies)
	{
		if (!enemy->isActive)
		{
			enemy->Spawn(pos);
			return;
		}
	}
}
