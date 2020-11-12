#pragma once

class Angie : public ImageRect
{
private:
	enum State
	{
		IDLE,
		RUN,
		ATTACK
	} state;

	vector<Animation*> animations;

	float speed;
	float jumpPower;
	float gravity;

	Texture* mountain;

	Shell* shell;

	HBRUSH brush;
	HPEN pen;

	void LoadXML(string path, string file);
	void SetAnimation(State state);
	void SetIdle();

	float GetMountainY(Vector2 pos);
public:
	Angie();
	~Angie();

	void Update();
	void Render();

	

	void Move();
	void Attack();
	void Jump();
};