#pragma once

class TileObjectManager : public Singleton<TileObjectManager>, public PoolingManager<TileObject>
{
private:
	friend class Singleton;

	const UINT POOL_SIZE = 50;

	TileObjectManager();
	~TileObjectManager();

public:
	void Update();
	void Render();

	TileObject* Collision(string key, Collider* collider);

public:
	TileObject* Spawn(const Vector2& pos, int power, wstring textureFile);
};