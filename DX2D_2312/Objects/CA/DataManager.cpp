#include "Framework.h"

DataManager::DataManager()
{
	LoadItemData();
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

		//key, name, hp, power, speed, type, value, Image 
		ItemData data;
		data.key = stoi(datas[0]);
		data.name = datas[1];
		data.power = stof(datas[2]);
		data.speed = stof(datas[3]);
		data.type = stoi(datas[4]);
		data.value = stoi(datas[5]);
		data.textureFile = ToWString(datas[6]);

		itemDatas[data.key] = data;
	}
}
