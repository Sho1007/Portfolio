#pragma once

class Landscape
{
private:
	const UINT LAND = 4;
	const UINT BLOCK = 5;
	ImageRect* sky[2];

	float skySpeed;

	vector<ImageRect*> lands;
	float landSpeed;

	vector<ImageRect*> blocks;

	Mario* mario;


	void CreateBG();
	void CreateLand();
	void CreateBlock();

	Rect* target;
public:
	Landscape();
	~Landscape();

	void Update();
	void Render();

	Direction PushCollision(Rect* rect);
	void SetMario(Mario* mario) { this->mario = mario; }
};