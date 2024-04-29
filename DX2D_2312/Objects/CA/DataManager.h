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

struct StageData
{
	int key;
	int num;
	int type;
	string stage1;
	string stage2;
	string stage3;
	int level;
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

	StageData GetStageData(int key) { return stageDatas[key]; }
	int SizeStageData() { return stageDatas.size(); }

private:
	void LoadItemData();
	void LoadMonsterData();
	void LoadStageData();

public:
	map<int, ItemData> itemDatas;
	map<int, MonsterData> monsterDatas;
	map<int, StageData> stageDatas;
};
