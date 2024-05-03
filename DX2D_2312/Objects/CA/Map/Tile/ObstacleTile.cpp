#include "Framework.h"

ObstacleTile::ObstacleTile(wstring textureFile, Vector2 pos, bool isPop)
	: Tile(textureFile, pos, Tile::OBSTACLE)
{
	this->isPop = isPop;
	SetColliderSize(TILE_SIZE, 0.9f);
}

ObstacleTile::~ObstacleTile()
{
}

void ObstacleTile::End()
{
	if (!isPop) return;

	SetActive(false);
	ItemManager::Get()->Spawn(GetGlobalPosition());
	EffectManager::Get()->Play("RemoveObstacle", GetGlobalPosition());
}
