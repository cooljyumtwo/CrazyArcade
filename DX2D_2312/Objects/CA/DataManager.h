#pragma once

struct ItemData
{
	int key;
	string name;
	int type;
	int value;
	int probability;
	wstring textureFile;
};

class DataManager : public Singleton<DataManager>
{
private:
	friend class Singleton;

	DataManager();
	~DataManager() = default;

public:
	ItemData GetItemData(int key) { return itemDatas[key]; }
	int SizeItemData() { return itemDatas.size(); }

private:
	void LoadItemData();

public:
	map<int, ItemData> itemDatas;
};
