#include "Framework.h"

BossAttack::BossAttack(Transform* target, int key, int max_frameX)
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Attack.png", max_frameX, 1, false, 1.7f);

	EffectManager::Get()->Add("MonsterSpawn", 50, L"MonsterSpawn.png",
		Vector2(4, 1), 0.5f);
}

void BossAttack::Start()
{
	CharacterAction::Start();

	if (!Audio::Get()->IsPlaySound("BossMonsterSpawn"))
		Audio::Get()->Play("BossMonsterSpawn");
}

void BossAttack::End()
{
	Boss* boss = (Boss*)target;
	boss->SetAction(boss->curType);

	Vector2 curIdx = Random({ 0,0 }, { (float)TileManager::Get()->SIZE_X ,(float)TileManager::Get()->SIZE_Y });
	Vector2 pos = TileManager::Get()->GetBgTile(curIdx)->GetGlobalPosition();

	int randomCompassType = Random(0, 2);
	if (randomCompassType)
	{
		Vector2 curPos = boss->GetCollider()->GetGlobalPosition();
		vector<Vector2> checkPos;

		vector<Vector2> offsets = {
			Vector2{-3, -3}, Vector2{-2, -3}, Vector2{-1, -3}, Vector2{0, -3}, Vector2{1, -3}, Vector2{2, -3}, Vector2{3, -3},
			Vector2{-3, -2}, Vector2{3, -2},
			Vector2{-3, -1}, Vector2{3, -1},
			Vector2{-3, 0}, Vector2{3, 0},
			Vector2{-3, 1}, Vector2{3, 1},
			Vector2{-3, 2}, Vector2{3, 2},
			Vector2{-3, 3}, Vector2{-2, 3}, Vector2{-1, 3}, Vector2{0, 3}, Vector2{1, 3}, Vector2{2, 3}, Vector2{3, 3}
		};

		for (const auto& offset : offsets) {
			checkPos.push_back(curPos + offset * Tile::TILE_SIZE);
		}

		for (Vector2 pos : checkPos)
		{
			Tile* tile = TileManager::Get()->GetNearPosTileState(pos);

			if (!tile) return;

			if (tile->GetType() == Tile::BASIC)
			{
				BubbleManager::Get()->Spawn(tile->GetGlobalPosition(), 1, boss);
			}
		}
	}
	else
		MonsterManager::Get()->Spawn(pos);
	EffectManager::Get()->Play("MonsterSpawn", pos);


}


