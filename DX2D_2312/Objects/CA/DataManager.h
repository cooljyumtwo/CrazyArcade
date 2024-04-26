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

struct MonsterData
{
	int key;
	string name;
	float speed;
	bool isBubble;
	int hp;
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

	MonsterData GetMonsterData(int key) { return monsterDatas[key]; }

private:
	void LoadItemData();
	void LoadMonsterData();

public:
	map<int, ItemData> itemDatas;
	map<int, MonsterData> monsterDatas;
};
