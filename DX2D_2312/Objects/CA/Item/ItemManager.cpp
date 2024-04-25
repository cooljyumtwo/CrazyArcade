#include "Framework.h"

ItemManager::ItemManager()
{
	totalObject["Item"].resize(TileManager::Get()->SIZE_X * TileManager::Get()->SIZE_Y);

	for (GameObject*& item : totalObject["Item"])
	{
		item = new Item();	
		RenderManager::Get()->Add("GameObject", item);
	}

	SetTotalProbability();
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

void ItemManager::SetTotalProbability()
{
	sizeItemDatas = DataManager::Get()->SizeItemData();

	FOR(sizeItemDatas)
		totalProbability += DataManager::Get()->GetItemData(1).probability;
}

void ItemManager::Spawn(const Vector2& pos)
{
	Item* item = Pop("Item", true);

	int random = Random(0, totalProbability);
	random %= sizeItemDatas;
	item->Spawn(pos, DataManager::Get()->GetItemData(random));
}

void ItemManager::Collision(Character* target)
{
	for (GameObject* object : totalObject["Item"])
	{
		if (!object->IsActive()) continue;

		Item* item = (Item*)object;
		if (item->GetCollider()->IsCollision(target->GetCollider()))
		{
			item->SetActive(false);

			Player* player = (Player*)target;
			player->AddItem(item);
		}
	}
}
