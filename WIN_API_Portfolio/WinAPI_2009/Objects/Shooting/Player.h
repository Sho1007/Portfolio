#pragma once

class Player : public ImageRect
{
private:
	enum State {
		IDLE,
		WALK_FRONT,
		LEFT,
		WALK_LEFT,
		RIGHT,
		WALK_RIGHT,
		BACK,
		WALK_BACK
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