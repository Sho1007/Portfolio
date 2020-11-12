#include "Framework.h"

DataManager::DataManager()
{
	LoadPlayerData();
}

DataManager::~DataManager()
{
	for (auto data: playerData)
	{
		delete data.second;
	}
}

void DataManager::LoadPlayerData()
{
	ifstream load("TextData/PlayerData.tsv", ios::in);

	string str;

	int count = 0;

	while (true)
	{
		count++;
		if (count <= 11)
		{
			load >> str;
			continue;
		}
		int key = 0;
		load >> key;
		if (key == 0)
			return;


		PlayerData* data = new PlayerData;

		data->key = key;
		load >> data->name >> data->attack >> data->speed >> data->accel >> data->hp >> data->image >> data->imageWidth >> data->imageHeight >> data->frameX >> data->frameY;

		playerData[key] = data;
	}
}
