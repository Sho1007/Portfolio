#pragma once

class HWBird : public ImageRect
{
private:
	const float F = 300.0f;

	enum ActionState
	{
		IDLE,
		JUMP,
	} state;

	vector<Animation*> animations;

	float jumpForce;
	float gravity;

	bool isJump;
	void Jump();

	void CreateActions();

	void SetAnimation(ActionState value);
public:
	HWBird();
	~HWBird();

	void Update();
	void Render();
};