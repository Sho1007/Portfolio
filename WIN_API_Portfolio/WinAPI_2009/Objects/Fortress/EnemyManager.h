#pragma once
#include "Enemy.h"
#include "ShellManager.h"

class EnemyManager
{
private:
	const int POOL_COUNT = 50;

	vector<Enemy*> enemies;

	float spawnTime;
	float time;

	BulletManager* bm;

	void Collision();
	void CreateEnemy();
public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Render();
	void SetBM(BulletManager* value) { bm = value; }
};