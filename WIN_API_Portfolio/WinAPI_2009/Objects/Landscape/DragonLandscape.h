#pragma once

class DragonLandscape
{
	ImageRect* sky[2];
	float skySpeed;

public:
	DragonLandscape();
	~DragonLandscape();

	void Update();
	void Render();

	void CreateBG();
};