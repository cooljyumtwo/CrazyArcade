#include "Framework.h"

DataManager::DataManager()
{
	LoadItemData();
	LoadMonsterData();
	LoadStageData();
	LoadTileData();
}

void DataManager::LoadItemData()
{
	ifstream loadFile(L"ResourcesCA/TextData/Data/ItemTable.csv");

	string temp;

	bool isFirstLine = true;

	while (!loadFile.eof())
	{
		getline(loadFile, temp);

		if (temp.size() == 0)
			return;

		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> datas = SplitString(temp, ",");

		ItemData data;
		data.key = stoi(datas[0]);
		data.name = datas[1];
		data.type = stoi(datas[2]);
		data.value = stoi(datas[3]);
		data.probability = stoi(datas[4]);
		data.textureFile = ToWString(datas[5]);

		itemDatas[data.key] = data;
	}
}

void DataManager::LoadMonsterData()
{
	ifstream loadFile(L"ResourcesCA/TextData/Data/MonsterTable.csv");

	string temp;

	bool isFirstLine = true;

	while (!loadFile.eof())
	{
		getline(loadFile, temp);

		if (temp.size() == 0)
			return;

		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> datas = SplitString(temp, ",");

		MonsterData data;
		data.key = stoi(datas[0]);
		data.name = datas[1];
		data.speed = stof(datas[2]);
		data.isBubble = stoi(datas[3]);
		data.hp = stoi(datas[4]);

		monsterDatas[data.key] = data;
	}
}

void DataManager::LoadStageData()
{
	ifstream loadFile(L"ResourcesCA/TextData/Data/StageTable.csv");

	string temp;

	bool isFirstLine = true;

	while (!loadFile.eof())
	{
		getline(loadFile, temp);

		if (temp.size() == 0)
			return;

		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> datas = SplitString(temp, ",");

		StageData data;
		data.key = stoi(datas[0]);
		data.num = stoi(datas[1]);
		data.type = stoi(datas[2]);
		data.stage1 = datas[3];
		data.stage2 = datas[4];
		data.stage3 = datas[5];
		data.level = stoi(datas[6]);

		stageDatas[data.key] = data;
	}
}

void DataManager::LoadTileData()
{
	ifstream loadFile(L"ResourcesCA/TextData/Data/TileTable.csv");

	string temp;

	bool isFirstLine = true;

	while (!loadFile.eof())
	{
		getline(loadFile, temp);

		if (temp.size() == 0)
			return;

		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> datas = SplitString(temp, ",");

		TileData data;
		data.key = stoi(datas[0]);
		data.num = stoi(datas[1]);
		data.isPop = stoi(datas[2]);
		data.isPush = stoi(datas[3]);

		tileDatas[data.key] = data;
	}
}
