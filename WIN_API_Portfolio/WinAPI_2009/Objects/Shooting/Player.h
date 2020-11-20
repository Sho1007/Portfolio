#pragma once

class Player : public ImageRect
{
private:
	enum State {
		IDLE,
		FRONT_WALK,
		LEFT,
		LEFT_WALK,
		RIGHT,
		RIGHT_WALK,
		BACK,
		BACK_WALK
	} state;
	const float MAX_SPEED = 30.0f;
	const float BULLET_SPEED = 400.0f;

	vector<Animation*> animations;

	float accel;
	float speed;
	float attack;

	HpBar* hpBar;

	int key;


	Vector2 velocity;

	BulletManager* bm;

	void Create();

	Map* map;

public:
	Player();
	~Player();

	void Update();
	void Redner();

	void Move();
	void Fire();

	void CreateActions();

	void DoAction();

	void SetAnimation(State state);

	void SetBM(BulletManager* value) { this->bm = value; }
	void SetMap(Map* value) { map = value; }
};