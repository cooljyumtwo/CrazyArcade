#include "Framework.h"

ShootingDataManager::ShootingDataManager()
{
	LoadSkillData();
	LoadEnemyDdata();
	LoadItemData();
	LoadLevelData();
}


void ShootingDataManager::LoadSkillData()
{
	ifstream loadFile(L"Resources/TextData/SkillTable.csv");

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

		SkillData data;
		data.key = stoi(datas[0]);
		data.name = datas[1];
		data.level = stoi(datas[2]);
		data.power = stoi(datas[3]);
		data.range = stof(datas[4]);
		data.amount = stoi(datas[5]);
		data.duration = stof(datas[6]);
		data.speed = stof(datas[7]);
		data.knockback = stof(datas[8]);

		skillDatas[data.key] = data;
	}
}

void ShootingDataManager::LoadEnemyDdata()
{
	ifstream loadFile(L"Resources/TextData/EnemyTable.csv");

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

		EnemyData data;
		data.key = stoi(datas[0]);
		data.name = datas[1];
		data.level = stoi(datas[2]);
		data.maxHp = stoi(datas[3]);
		data.power = stof(datas[4]);		
		data.range = stof(datas[5]);
		data.speed = stof(datas[6]);
		data.type = stoi(datas[7]);
		data.textureFile = ToWString(datas[8]);

		enemyDatas[data.key] = data;
	}
}

void ShootingDataManager::LoadItemData()
{
	ifstream loadFile(L"Resources/TextData/ItemTable.csv");

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
		data.hp = stoi(datas[2]);
		data.power = stof(datas[3]);		
		data.speed = stof(datas[4]);
		data.type = stoi(datas[5]);
		data.value = stoi(datas[6]);
		data.textureFile = ToWString(datas[7]);

		itemDatas[data.key] = data;
	}
}

void ShootingDataManager::LoadLevelData()
{
	ifstream loadFile(L"Resources/TextData/LevelTable.csv");

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

		LevelData data;
		data.key = stoi(datas[0]);
		data.exp = stoi(datas[1]);
		data.power = stof(datas[2]);
		data.hp = stoi(datas[3]);		
		data.speed = stof(datas[4]);		

		levelDatas[data.key] = data;
	}
}
