#include "Framework.h"

ObstacleTile::ObstacleTile(wstring textureFile, Vector2 pos, bool isPop, bool isPush)
	: Tile(textureFile, pos, Tile::OBSTACLE), isPop(isPop), isPush(isPush)
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

void ObstacleTile::SetTarget(GameObject* target)
{
	if (isMove)
		return;

	this->target = target;

	isMove = true;

	Tile* tile = (Tile*)target;
	SetCurIdx(tile->GetCurIdx());
}

void ObstacleTile::Move()
{
	if (target == nullptr)
		return;

	float distance = Distance(localPosition, target->GetLocalPosition());

	if (distance < OFFSET_DISTANCE)
	{
		isMove = false;
		target = nullptr;

		return;
	}

	SetLocalPosition(Lerp(localPosition, target->GetLocalPosition(), DELTA * speed));
}

void ObstacleTile::Deactivate()
{
	if (!isPop) return;

	SetActive(false);
	ItemManager::Get()->Spawn(GetGlobalPosition());
	EffectManager::Get()->Play("RemoveObstacle", GetGlobalPosition());
}
