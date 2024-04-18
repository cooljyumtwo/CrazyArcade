#include "Framework.h"

BubbleManager::BubbleManager()
{
	totalObject["BasicBubble"].resize(POOL_SIZE);

	for (GameObject*& bubble : totalObject["BasicBubble"]) 
	{
		bubble = new Bubble();
		RenderManager::Get()->Add("GameObject", bubble);
	}
}

BubbleManager::~BubbleManager()
{
}

void BubbleManager::Render()
{
	for (GameObject*& bubble : totalObject["BasicBubble"])
		bubble->Render();

}

void BubbleManager::Update()
{
	for (GameObject*& bubble : totalObject["BasicBubble"])
		bubble->Update();

}

Bubble* BubbleManager::Collision(string key, Collider* collider)
{
	for (GameObject* bullet : totalObject[key])
	{
		if (((Bubble*)bullet)->GetCollider()->IsCollision(collider))
		{
			return (Bubble*)bullet;
		}
	}

	return nullptr;
}

void BubbleManager::Spawn(const Vector2& pos, int power)
{
	Pop("BasicBubble")->Spawn(pos, power);
}
