#pragma once

class TileManager : public Singleton<TileManager>, Transform
{
private:
	string PATH = "ResourcesCA/TextData/Map/";

	UINT SIZE_X = 15;
	UINT SIZE_Y = 13;
private:
	friend class Singleton;

	TileManager();
	~TileManager();

public:
	void Render();
	void Update();

	void SetMap(string mapNameStr) { this->mapNameStr = mapNameStr; }

	void SetBGTile(vector<vector<Tile*>> bgTiles) { this->bgTiles = bgTiles; }
	vector<vector<Tile*>> GetBGTile() { return bgTiles; }

	void SetIdxBgTileType(Vector2 idx,Tile::Type type) { bgTiles[idx.x][idx.y]->SetType(type); }

	void CreateBGTile();
	void LoadMapData(string file);
	void LoadGameMap() { LoadMapData(PATH + mapNameStr + ".map"); }

	void ClearObjTile();
	void AddObjTile(const Vector2& pos, const Vector2& size, const Vector2 idx, const wstring textureFile);

	Tile* SetNearPosState(GameObject* target, Tile::Type type = Tile::BASIC);

	void PushPlayer(Character* player, Vector2 velocity);

public:

	GameObject* tiles;
	vector<vector<Tile*>> bgTiles;
	vector<ObstacleTile*> objTiles;

	vector<GameObject*> gameObjects;

	string mapNameStr="Map1";

	Vector2 tileSize;
};