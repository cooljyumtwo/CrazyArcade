#include "Framework.h"

ItemManager::ItemManager()
{
	totalObject["Item"].resize(300);

	for (GameObject*& item : totalObject["Item"])
	{
		item = new Item();	
		RenderManager::Get()->Add("GameObject", item);
	}
}

ItemManager::~ItemManager()
{
}

void ItemManager::Update()
{
	for (const auto& pair : totalObject) {
		const vector<GameObject*>& gameObjects = pair.second;
		for (GameObject* object : gameObjects) {
			object->Update();
		}
	}
}

void ItemManager::Render()
{
}

void ItemManager::Spawn(const Vector2& pos)
{
	Item* item = Pop("Item", true);

	//int random = Random(0, 100);

	ItemData data;	
	//if (random < 50)
	//{
	//	random = Random(1, 4);
	//	int type = 0;
	//	if (random == 1)
	//		type = Random(0, 2);

	//	int level = Random(0, 100);
	//	if (level < 10)
	//		level = 3;
	//	else if (level < 30)
	//		level = 2;
	//	else
	//		level = 1;

	//	int key = random * 100 + type * 10 + level;
	//	data = DataManager::Get()->GetItemData(key);
	//}
	//else if(random < 60)
	//	data = DataManager::Get()->GetItemData(1);
	//else if(random < 90)
	//	data = DataManager::Get()->GetItemData(2);
	//else

	data = DataManager::Get()->GetItemData(1);

	item->Spawn(pos, data);
}

Item* ItemManager::Collision(Collider* collider)
{
	for (GameObject* object : totalObject["Item"])
	{
		Item* item = (Item*)object;

		if (item->IsField() && item->GetCollider()->IsCollision(collider))
		{
			return item;
		}
	}

	return nullptr;
}
