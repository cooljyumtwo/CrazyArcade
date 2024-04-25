#include "Framework.h"

MonsterManager::MonsterManager()
{
	totalObject["Monster"].resize(4);

	MonsterData monsterData;
	monsterData = DataManager::Get()->GetMonsterData(0);

	for (GameObject*& monster : totalObject["Monster"])
	{
		monster = new Monster(monsterData.key, monsterData.speed, monsterData.isBubble);
		RenderManager::Get()->Add("GameObject", monster);
	//	Tile* tile = TileManager::Get()->GetBgTile(Vector2{ (float)Random(3,10), (float)Random(3,10) });
		//MonsterManager::Get()->Spawn(tile->GetGlobalPosition());
	}
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::Update()
{
	for (const auto& pair : totalObject) {
		const vector<GameObject*>& gameObjects = pair.second;
		for (GameObject* object : gameObjects) {
			object->Update();
		}
	}
}

void MonsterManager::Render()
{
}

void MonsterManager::Spawn(const Vector2& pos)
{
	Monster* monster = Pop("Monster", true);
	monster->Spawn(pos);
}

void MonsterManager::Collision(Character* target)
{
	for (GameObject* object : totalObject["Item"])
	{
		if (!object->IsActive()) continue;

		Monster* monster = (Monster*)object;
		if (monster->GetCollider()->IsCollision(target->GetCollider()))
		{
			monster->SetActive(false);

			Player* player = (Player*)target;
		}
	}
}
