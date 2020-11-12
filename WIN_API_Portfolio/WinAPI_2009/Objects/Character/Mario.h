#pragma once
#include "Objects/Landscape/HWBlockManager.h"

class Mario : public ImageRect
{
private:	
	const float F = 700.0f;

	enum ActionState
	{
		IDLE,
		R_WALK,
		L_WALK,
		R_JUMPUP,
		L_JUMPUP,
		R_JUMPDOWN,
		L_JUMPDOWN,
		R_ATTACK,
		L_ATTACK
	}state;

	Direction colDir;

	vector<Animation*> animations;


	float speed;
	float jumpForce;
	float gravity;

	bool isRight;
	bool isJump;
	class Landscape* landscape;
	class HWBlockManager* bm;
public:
	Mario();
	~Mario();

	void Update();
	void Render();

	void SetLandscape(class Landscape* value) { landscape = value; }
	void SetBlockManager(class HWBlockManager* value) { bm = value; }

	float GetJumpForce() { return this->jumpForce; }

private:
	void Move();
	void Jump();
	void Attack();
	void CreateActions();

	void SetAnimation(ActionState value);

	void SetIdle();
};