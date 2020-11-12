#pragma once

class HWBlockManager
{
	Texture* blockTexture;
	float blockSpeed;
	vector<ImageRect*> blocks;

	int coinCount;
public:
	HWBlockManager();
	~HWBlockManager();

	void Update();
	void Render();

	Direction PushCollision(Rect* rect);
};