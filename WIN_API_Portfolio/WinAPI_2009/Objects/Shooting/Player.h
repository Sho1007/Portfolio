#pragma once

class Player : public ImageRect
{
private:

	const float MAX_SPEED = 30.0f;
	const float BULLET_SPEED = 400.0f;

	float accel;
	float speed;
	float attack;

	HpBar* hpBar;

	int key;


	Vector2 velocity;

	BulletManager* bm;

	void Create();

public:
	Player();
	~Player();

	void Update();
	void Redner();

	void Move();
	void Fire();

	void SetBM(BulletManager* value) { this->bm = value; }
};