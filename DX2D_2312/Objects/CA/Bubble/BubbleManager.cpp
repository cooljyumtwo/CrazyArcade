#include "Framework.h"

BubbleManager::BubbleManager()
{
	totalObject["BasicBubble"].resize(POOL_SIZE);

	for (GameObject*& bubble : totalObject["BasicBubble"]) 
	{
		bubble = new Bubble();
		RenderManager::Get()->Add("GameObject", bubble);
	}

	totalObject["BasicWaves"].resize(POOL_SIZE);

	for (GameObject*& waves : totalObject["BasicWaves"])
	{
		waves = new Waves();
		RenderManager::Get()->Add("GameObject", waves);
	}
}

BubbleManager::~BubbleManager()
{
}

void BubbleManager::Render()
{
}

void BubbleManager::Update()
{
	for (GameObject*& bubble : totalObject["BasicBubble"])
		bubble->Update();

	for (GameObject*& waves : totalObject["BasicWaves"])
		waves->Update();
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
	Bubble* bubble = (Bubble*)Pop("BasicBubble");
	bubble->Spawn(pos, power);
}

void BubbleManager::SpawnWaves(const Vector2& pos, int power)
{
	Waves* wave = (Waves*)Pop("BasicWaves");
	wave->Spawn(pos, power);
}
