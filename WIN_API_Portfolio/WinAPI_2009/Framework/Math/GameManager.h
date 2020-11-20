#pragma once

class GameManager
{	
	bool play;
	bool debugMode;
	float timeCool;
	float timeCoolNow;
	UINT min;
	UINT hour;
	UINT day;


	void Create();
	void Destroy();
	GameManager();
	~GameManager();
public:
	static GameManager* Get()
	{
		static GameManager instance;
		return &instance;
	}

	void Update();
	void Render(HDC hdc) const;

	void DebugSwitch();
	bool IsDebug() const { return debugMode; }

	void SetPlay(bool value) { play = value; }
	bool IsPlay() const { return play; }

	UINT GetDay() { return day; }
	UINT GetHour() { return hour; }
	UINT GetMin() { return min; }
};