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

	void SetBGTile(vector<vector<Tile*>> bgTiles) { this->bgTiles = bgTiles; }
	vector<vector<Tile*>> GetBGTile() { return bgTiles; }

	void CreateBGTile();
	void LoadMapData(string file);
	void LoadGameMap() { LoadMapData(PATH + mapNameStr + ".map"); }

	void ClearObjTile();
	void AddObjTile(const Vector2& pos, const Vector2& size, const Vector2 idx, const wstring textureFile);

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

	string mapNameStr="Map1";

	Vector2 tileSize;
};