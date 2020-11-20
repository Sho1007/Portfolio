#pragma once

class EnemyManager
{
	float spawnTime;
	float spawnTimeNow;

	

	Rect* player;
	Map* map;

	void Create();
	void Destroy();
	void CheckCollision(Enemy* rc1, Enemy* rc2);
	void SpawnEnemy();
	
public:
	vector<Enemy*> enemies;

	EnemyManager(Rect* player, Map* map);
	~EnemyManager();

	void Update();
	void Render();	
};