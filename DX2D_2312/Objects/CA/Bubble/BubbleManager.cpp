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

void BubbleManager::Spawn(const Vector2& pos, int power, Character* target)
{
	Bubble* bubble = (Bubble*)Pop("BasicBubble");
	bubble->Spawn(pos, power, target);
}

void BubbleManager::SpawnWaves(const Vector2& pos, int power)
{
	Waves* wave = (Waves*)Pop("BasicWaves");
	wave->Spawn(pos, power);
}

void BubbleManager::PushPlayer(Character* player)
{
	for (GameObject*& bubbleObj : totalObject["BasicBubble"])
	{
		Bubble* bubble = (Bubble*)bubbleObj;
		Vector2 overlab;

		if (bubble->GetCollider()->IsCollision(player->GetCollider(), &overlab))
		{
			if (overlab.x > 20.0f) return;

			if (overlab.x < overlab.y)
			{
				if (player->GetGlobalPosition().x > bubble->GetGlobalPosition().x)
				{
					player->Translate(Vector2::Right() * overlab.x);
				}
				else
				{
					player->Translate(Vector2::Left() * overlab.x);
				}
			}
			else
			{
				if (player->GetGlobalPosition().y > bubble->GetGlobalPosition().y)
				{
					player->Translate(Vector2::Up() * overlab.y);
				}
				else
				{
					player->Translate(Vector2::Down() * overlab.y);
				}
			}

			player->UpdateWorld();
		}
	}
}
