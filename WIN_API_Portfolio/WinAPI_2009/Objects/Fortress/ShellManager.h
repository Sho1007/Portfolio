#pragma once
#include "Shell.h"

class ShellManager
{
private:
	const int POOL_COUNT = 50;

	vector<Shell*> shells;

public:
	ShellManager();
	~ShellManager();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector2 pos, float angle, float speed);

	bool IsCollision(Object* object);
};