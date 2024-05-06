#include "Framework.h"

ObstacleTile::ObstacleTile(wstring textureFile, Vector2 pos, bool isPop, bool isPush)
	: Tile(textureFile, pos, Tile::OBSTACLE), isPop(isPop), isPush(isPush), targetPos(pos)
{
	SetColliderSize(TILE_SIZE, 0.9f);
}

ObstacleTile::~ObstacleTile()
{
}

void ObstacleTile::Update()
{
	Quad::Update();
	Move();
}

void ObstacleTile::Move()
{
	SetLocalPosition(Lerp(localPosition, targetPos, DELTA));
}

void ObstacleTile::Deactivate()
{
	if (!isPop) return;

	SetActive(false);
	ItemManager::Get()->Spawn(GetGlobalPosition());
	EffectManager::Get()->Play("RemoveObstacle", GetGlobalPosition());
}
