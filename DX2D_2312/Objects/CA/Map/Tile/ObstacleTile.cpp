#include "Framework.h"

ObstacleTile::ObstacleTile(wstring textureFile, Vector2 pos, bool isPop)
	: Tile(textureFile, pos, Tile::OBSTACLE)
{
	this->isPop = isPop;
}

ObstacleTile::~ObstacleTile()
{
}

void ObstacleTile::End()
{
	SetActive(false);
	EffectManager::Get()->Play("RemoveObstacle", GetGlobalPosition());
}
