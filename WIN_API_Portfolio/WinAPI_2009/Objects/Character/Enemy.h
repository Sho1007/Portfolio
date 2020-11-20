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
	Rect colRect;
	vector<Animation*> animations;
	Map* map;

	friend class EnemyManager;

	void CreateActions();
	void SetIdle();
	void SetAnimation(State value);
	void Create();
	void Destroy();
	void SetTarget(Rect* value) { target = value; }
	void SetMap(Map* value) { map = value; }
	void SetSpawn(Vector2 pos);
public:
	
	void Update();
	void Render();
	Enemy();
	~Enemy();

	bool operator< (const Enemy& e) const
	{
		if (this->center.y < e.center.y)
			return true;

		return false;
	}

	static int Compare(Enemy* e1, Enemy* e2);
};