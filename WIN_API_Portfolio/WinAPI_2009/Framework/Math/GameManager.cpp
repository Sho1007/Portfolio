#include "Framework.h"

GameManager::GameManager()
{
	Create();
}

GameManager::~GameManager()
{
	Destroy();
}

void GameManager::Create()
{
	debugMode = false;
	timeCool = 0.01f;
	timeCoolNow = 0.0f;

	min = 0;
	hour = 0;
	day = 0;
}

void GameManager::Destroy()
{
}

void GameManager::Update()
{
	DebugSwitch();
	if (play)
	{
		timeCoolNow += DELTA;
		if (timeCoolNow >= timeCool)
		{
			timeCoolNow -= timeCool;
			min += 1;
		}

		if (min >= 60)
		{
			min -= 60;
			hour += 1;
		}

		if (hour >= 24)
		{
			hour -= 24;
			day += 1;
		}
	}
}

void GameManager::Render(HDC hdc) const 
{
	if (debugMode)
	{
		string temp = debugMode == true ? "true" : "false";
		string str = "DebugMode : " + temp;
		TextOutA(hdc, CENTER_X, 20, str.c_str(), str.length());

		if (play)
		{
			str = "Day : " + to_string(day) + ", hour : " + to_string(hour) + ", min : " + to_string(min);
			TextOutA(hdc, CENTER_X, 50, str.c_str(), str.length());
		}
	}
}

void GameManager::DebugSwitch()
{
	if (KEY_DOWN(VK_F3))
	{
		if (debugMode)
			debugMode = false;
		else
			debugMode = true;
	}		
}
