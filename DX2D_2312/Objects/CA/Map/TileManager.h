#pragma once

class TileManager : public Singleton<TileManager>
{
private:
	string PATH = "ResourcesCA/TextData/Map/";

	UINT SIZEX=15;
	UINT SIZEY=13;
private:
	friend class Singleton;

	TileManager();
	~TileManager();

public:
	void Render();
	void Update();

	void SetMap(string mapNameStr) { this->mapNameStr = mapNameStr; }

	void CreateBGTile();
	void LoadMapData(string file);
	void ClearObjTile();

	void SetNearPosState(RectCollider* target,Tile::Type type);
	Tile* SetNearPosState(RectCollider* target);
public:
	Tile* Collision(string key, Collider* collider);

public:
	//void Spawn(const Vector2& pos, int power);

	vector<Tile*> bgTiles;
	vector<ObstacleTile*> objTiles;

	string mapNameStr="Map";

	Vector2 tileSize;
};