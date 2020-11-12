#pragma once

class HWDragonEnemyManager
{
	bool bossCreate;
	UINT POOL_COUNT = 50;
	vector<HWDragonEnemy*> enemies;

	float respawnTime;
	float respawnDelay;

	BulletManager* bm;
	HWDragonPlayer* player;

	
	void Destroy();
public:
	HWDragonEnemyManager();
	~HWDragonEnemyManager();

	void Create();
	void Update();
	void Render();
	void SetBM(BulletManager* value) { bm = value; }
	void SetPlayer(HWDragonPlayer* value) { player = value; }
};