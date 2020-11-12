#pragma once

class GameManager
{
	UINT stage;
	bool isPlay;
	int gold;
	
	GameManager();
	~GameManager();

public:
	static GameManager* Get()
	{
		GameManager instance;
		return &instance;
	}

	void Render(HDC hdc);
	bool Pay(int value);

	void Init();
};