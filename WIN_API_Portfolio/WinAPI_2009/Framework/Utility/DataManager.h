#pragma once

struct PlayerData
{
	int key;
	string name;
	float attack;
	float speed;
	float accel;
	float hp;
	string image;
	int imageWidth;
	int imageHeight;
	int frameX;
	int frameY;
};

class DataManager
{
private:
	map<int, PlayerData*> playerData;
	int selectPlayerNum;


	DataManager();
	~DataManager();
public:
	static DataManager* Get()
	{
		static DataManager instance;
		return &instance;
	}

	//PlayerData* GetPlayerData(int key) { return playerData[key]; }
	//UINT GetPlayerDataSize() { return playerData.size(); }
	map<int, PlayerData*> GetPlayerData() { return playerData; }
	int GetSelectNum() { return selectPlayerNum; }
	void SetSelectNum(int value) { selectPlayerNum = value; }
private:
	void LoadPlayerData();
};