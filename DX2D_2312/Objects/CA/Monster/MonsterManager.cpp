#include "Framework.h"

MonsterManager::MonsterManager()
{
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::Update()
{
	//if (!isRoad) return;

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

void MonsterManager::LoadBossMonster()
{
	totalObject["SpawnBossMonster"].resize(10);

	for (GameObject*& monsterObj : totalObject["SpawnBossMonster"])
	{
		int key = Random(0,4);

		MonsterData monsterData;
		monsterData = DataManager::Get()->GetMonsterData(key);

		monsterObj = new Monster(monsterData.key, monsterData.speed, monsterData.isBubble, monsterData.hp);

		Monster* monster = (Monster*)monsterObj;

		RenderManager::Get()->Add("GameObject", monster);
	}
}

void MonsterManager::Spawn(const Vector2& pos)
{
	Pop("SpawnBossMonster")->Spawn(pos);
	spawnMonster++;
}

void MonsterManager::LoadMonster()
{
	ClearMonster();

	killMonster = 0;
	spawnMonster = 0;
	cntBoss = 0;

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

		if (key >= CHECK_BOSS_IDX)
		{
			monsterObj = new Boss(monsterData.key, monsterData.speed, monsterData.isBubble, monsterData.hp);
			Boss* monster = (Boss*)monsterObj;
			monster->Spawn(pos);
			RenderManager::Get()->Add("GameObject", monster);

			LoadBossMonster();

			cntBoss++;

			isSpawnBoss = true;
		}
		else 
		{
			monsterObj = new Monster(monsterData.key, monsterData.speed, monsterData.isBubble, monsterData.hp);
			spawnMonster++;
			Monster* monster = (Monster*)monsterObj;
			monster->Spawn(pos);
			RenderManager::Get()->Add("GameObject", monster);
		}
	}

	isRoad = true;
	delete reader;
}

void MonsterManager::ClearMonster()
{
//	isRoad = false;

	for (auto& pair : totalObject)
	{
		vector<GameObject*>& gameObjects = pair.second;
		for (GameObject*& object : gameObjects)
		{
			object->SetActive(false);
		}
	}
}

void MonsterManager::Collision(Character* character)
{
	if (!isRoad) return;

	for (const auto& pair : totalObject)
	{
		const vector<GameObject*>& gameObjects = pair.second;
		for (GameObject* object : gameObjects)
		{
			Monster* monster = (Monster*)object;
			if(monster->IsActive())
				monster->Collision(character);
		}
	}
}

void MonsterManager::AddKillMonster(bool isBoss)
{
	killMonster++;

	if (isBoss)
		cntBoss--;

	if ((isSpawnBoss || killMonster >= spawnMonster) && cntBoss <= 0)
	{
		isRoad = false;
		StageManager::Get()->Clear();
	}
}
