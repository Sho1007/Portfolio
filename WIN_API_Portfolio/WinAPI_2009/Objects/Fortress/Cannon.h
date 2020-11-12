#pragma once
#include "ShellManager.h"

class Cannon
{
private:
	Circle* body;//¸öÅë
	Line* barrel;//Æ÷½Å

	float angle;
	float barrelLength;

	float power;
	float powerSpeed;

	float moveSpeed;

	ShellManager* sm;

	HBRUSH brushes[2];
	HBRUSH oldBrush;

	Rect* powerFrontBar;
	Rect* powerBackBar;
public:
	Cannon();
	~Cannon();

	void Update();
	void Render(HDC hdc);

	ShellManager* GetSM() { return sm; }
};