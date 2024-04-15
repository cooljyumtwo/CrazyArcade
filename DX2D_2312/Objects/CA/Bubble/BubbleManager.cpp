#include "Framework.h"

BubbleManager::BubbleManager()
{
	totalObject["BasicBubble"].resize(POOL_SIZE);

	for (GameObject*& bubble : totalObject["BasicBubble"])
		bubble = new Bubble();
}

BubbleManager::~BubbleManager()
{
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
