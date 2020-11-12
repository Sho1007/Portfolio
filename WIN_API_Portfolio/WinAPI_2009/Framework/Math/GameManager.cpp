#include "Framework.h"

GameManager::GameManager()
	: gold(0), isPlay(false), stage(1)
{
}

GameManager::~GameManager()
{
}

void GameManager::Render(HDC hdc)
{
	string temp = "Gold : " + to_string(gold);
	TextOutA(hdc, WIN_WIDTH - 150, 100, temp.c_str(), temp.length());
}

bool GameManager::Pay(int value)
{
	if (gold > value)
	{
		gold -= value;
		return true;
	}
	return false;
}

void GameManager::Init()
{
	gold = 0;
	isPlay = true;
	stage = 1;
}
