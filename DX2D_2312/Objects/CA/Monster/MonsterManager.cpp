#include "Framework.h"

MonsterManager::MonsterManager()
{
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::Update()
{
	if (!isRoad) return;

	for (const auto& pair : totalObject) 
	{
		const vector<GameObject*>& gameObjects = pair.second;
		for (GameObject* object : gameObjects) 
		{
			if(object)
				object->Update();
		}
	}
	if (boss)
		boss->Update();
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
		//monster->Spawn(pos);

		RenderManager::Get()->Add("GameObject", monster);
	}
}

void MonsterManager::Spawn(const Vector2& pos)
{
	Pop("SpawnBossMonster")->Spawn(pos);
	spawnMonster++;
}

void MonsterManager::BossSpawn(const Vector2& pos)
{
	boss = new Boss(101, 30.0f, true, 1);
	RenderManager::Get()->Add("GameObject", boss);
	boss->Spawn(pos);

	LoadBossMonster();
}

void MonsterManager::LoadMonster()
{
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

		if (key>=100)
		{
			monsterObj = new Boss(monsterData.key, monsterData.speed, monsterData.isBubble, monsterData.hp);
			Boss* monster = (Boss*)monsterObj;
			monster->Spawn(pos);
			RenderManager::Get()->Add("GameObject", monster);

			LoadBossMonster();

			cntBoss++;
		}
		else {
			monsterObj = new Monster(monsterData.key, monsterData.speed, monsterData.isBubble, monsterData.hp);
			spawnMonster++;
			Monster* monster = (Monster*)monsterObj;
			monster->Spawn(pos);
			RenderManager::Get()->Add("GameObject", monster);
		}

		
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
	if (boss)
	{
		RenderManager::Get()->Remove("GameObject", boss);
		delete boss;
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
			monster->Collision(character);
		}
	}
	if(boss)
		boss->Collision(character);
}

void MonsterManager::AddKillMonster(bool isBoss)
{
	killMonster++;

	if (isBoss)
		cntBoss--;

	if (killMonster >= spawnMonster && cntBoss <= 0)
		StageManager::Get()->Clear();
}
