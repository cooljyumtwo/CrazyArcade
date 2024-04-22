#pragma once

struct ItemData
{
	int key;
	string name;
	float power;
	float speed;
	int type;
	int value;
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

private:
	void LoadItemData();
public:
	map<int, ItemData> itemDatas;
};