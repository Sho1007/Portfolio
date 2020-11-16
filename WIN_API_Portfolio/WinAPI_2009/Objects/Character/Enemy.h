#pragma once

class Enemy : public ImageRect
{
	enum State
	{
		FRONT,
		FRONT_WALK,
		FRONT_ATTACK,
		LEFT,
		LEFT_WALK,
		LEFT_ATTACK,
		RIGHT,
		RIGHT_WALK,
		RIGHT_ATTACK,
		BACK,
		BACK_WALK,
		BACK_ATTACK
	} state;
	HpBar* hpBar;
	float speed;
	float attack;
	float atkCool;
	float atkCoolNow;
	Rect* target;
	Vector2 dir;
	Rect toward;
	vector<Animation*> animations;
	Map* map;

	void CreateActions();
	void SetIdle();
	void SetAnimation(State value);
public:
	void Create();
	void Destroy();
	void Update();
	void Render();
	void SetTarget(Rect* value) { target = value; }
	void SetMap(Map* value) { map = value; }
	
	Enemy();
	~Enemy();
};