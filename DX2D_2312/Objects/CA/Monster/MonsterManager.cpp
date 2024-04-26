#include "Framework.h"

MonsterManager::MonsterManager()
{
	//totalObject["Monster"].resize(4);

	//MonsterData monsterData;
	//monsterData = DataManager::Get()->GetMonsterData(0);

	//for (GameObject*& monster : totalObject["Monster"])
	//{
	//	monster = new Monster(monsterData.key, monsterData.speed, monsterData.isBubble);
	//	RenderManager::Get()->Add("GameObject", monster);
	//}
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::Update()
{
	for (const auto& pair : totalObject) 
	{
		const vector<GameObject*>& gameObjects = pair.second;
		for (GameObject* object : gameObjects) 
		{
			if(object)
				object->Update();
		}
	}
}

void MonsterManager::Render()
{
}

void MonsterManager::Spawn(const Vector2& pos)
{
	//Monster* monster = Pop("Monster", true);
	//monster->Spawn(pos);
}

void MonsterManager::LoadMonster()
{
	BinaryReader* reader = new BinaryReader(PATH + TileManager::mapNameStr + ".map");

	if (reader->IsFailed())
	{
		delete reader;
		return;
	}

	int size = reader->UInt();

	totalObject["LoadMonster"].resize(size);

	for (GameObject*& monsterObj : totalObject["LoadMonster"])
	{
		int key = reader->Int();
		Vector2 curIdx = reader->Vector();
		Vector2 pos = TileManager::Get()->GetBgTile(curIdx)->GetGlobalPosition();

		MonsterData monsterData;
		monsterData = DataManager::Get()->GetMonsterData(key);

		monsterObj = new Monster(monsterData.key, monsterData.speed, monsterData.isBubble, monsterData.hp);

		Monster* monster = (Monster*)monsterObj;
		monster->Spawn(pos);

		RenderManager::Get()->Add("GameObject", monster);
	}

	delete reader;
}

void MonsterManager::ClearMonster()
{
	for (auto& pair : totalObject)
	{
		vector<GameObject*>& gameObjects = pair.second;
		for (GameObject*& object : gameObjects)
		{
			RenderManager::Get()->Remove("GameObject", object);
			delete object;
		}
	}
}
