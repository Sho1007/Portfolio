#pragma once

class Shell
{
private:
	const float G = 980.0f;

	Circle* ball;

	float angle;
	float speed;

	bool isFire;

	float gravity;

public:
	Shell();
	~Shell();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector2 pos, float angle, float power);

	bool IsFire() { return isFire; }
	Circle* GetBall() { return ball; }
	void SetFire(bool value) { isFire = value; }
};