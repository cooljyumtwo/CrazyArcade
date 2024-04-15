#pragma once

class TileManager : public Singleton<Tile>
{
private:
	friend class Singleton;

	TileManager();
	~TileManager();

	void SaveMapData(string file);
	void LoadMapData(string file);

public:
	Tile* Collision(string key, Collider* collider);

public:
	void Spawn(const Vector2& pos, int power);
};