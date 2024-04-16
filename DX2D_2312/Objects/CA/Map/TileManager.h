#pragma once

class TileManager : public Singleton<TileManager>, Quad
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
	void PreRender();
	void Render();
	void PostRender();
	void Update();

	void SetMap(string mapNameStr) { this->mapNameStr = mapNameStr; }

	void CreateBGTile();
	void LoadMapData(string file);
	void ClearObjTile();

	//void SetNearPosState(RectCollider* target,Tile::Type type);
	Tile* SetNearPosState(GameObject* target, Tile::Type type = Tile::BASIC);

public:
	Tile* Collision(string key, Collider* collider);

public:
	//void Spawn(const Vector2& pos, int power);

	GameObject* tiles;
	vector<vector<Tile*>> bgTiles;
	vector<ObstacleTile*> objTiles;

	vector<GameObject*> gameObjects;

	string mapNameStr="Map";

	Vector2 tileSize;
};