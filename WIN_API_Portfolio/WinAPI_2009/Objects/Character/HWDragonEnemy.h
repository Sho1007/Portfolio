#pragma once

class HWDragonEnemy : public ImageRect
{
	bool isBoss;

	UINT enemyType;

	float speed;

	HpBar* hpBar;

	float fireDelay;
	float fireTime;

	float bulletSpeed;
	float bulletPower;
	POINT bulletFrame;

	Vector2 velocity;

	Animation* animation;

	BulletManager* bm;
	HWDragonPlayer* player;
	
	void Destroy();
	void Fire();
	void FireBoss();

public:
	HWDragonEnemy();
	~HWDragonEnemy();

	void Create(UINT enemyType);
	void CreateBoss();
	void Update();
	void Render();
	bool GetIsBoss() { return isBoss; }
	void SetBM(BulletManager* value) { bm = value; }
	void SetPlayer(HWDragonPlayer* value) { player = value; }
	void Damage(float dmg) override
	{
		hpBar->Damage(dmg);
	}
	float GetHp() { return hpBar->GetHp(); }
};