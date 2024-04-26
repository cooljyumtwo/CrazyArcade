#include "Framework.h"

TileObjectManager::TileObjectManager()
{
	totalObject["BasicObstacle"].resize(POOL_SIZE);

	for (GameObject*& obstacle : totalObject["BasicObstacle"])
		obstacle = new TileObject();
}

TileObjectManager::~TileObjectManager()
{
}

void TileObjectManager::Update()
{
	for (GameObject*& obstacle : totalObject["BasicObstacle"])
	{
		
		((TileObject*)obstacle)->Update();

	}
}


void TileObjectManager::Render()
{
	for (GameObject*& obstacle : totalObject["BasicObstacle"])
		((TileObject*)obstacle)->Render();
}

TileObject* TileObjectManager::Collision(string key, Collider* collider)
{
	return nullptr;
}

TileObject* TileObjectManager::Spawn(const Vector2& pos, int power, wstring textureFile)
{
	TileObject* obstacle = Pop("BasicObstacle");
	obstacle->Spawn(pos, textureFile);

	return obstacle;
}
