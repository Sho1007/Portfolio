#pragma once

class HWDragonPlayer : public ImageRect
{
	enum attackState
	{
		NONE,
		DOUBLE,
		TRIPLE
	} atkState;
	UINT powerState;

	float fireDelay;
	float fireTime;

	float bulletSpeed;
	float bulletPower;
	POINT bulletFrame;

	Vector2 velocity;

	Animation* animation;

	HpBar* hpBar;

	BulletManager* bm;

	float speed;
	float attack;

	void Create();
	void Destroy();
	void Move();
	void Fire();
	void SetPowerState(UINT value);

public:
	HWDragonPlayer();
	~HWDragonPlayer();
	void Update();
	void Render();
	void GetPowerUp();
	void Damage(float dmg) override;
	
	
	void SetBM(BulletManager* value) { bm = value; }
};