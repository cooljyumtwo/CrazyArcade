#pragma once

class TileManager : public Singleton<TileManager>, Transform
{
public:
	UINT SIZE_X = 15;
	UINT SIZE_Y = 13;

private:
	string PATH = "ResourcesCA/TextData/Map/";
	float OFFSET = 10.0f;

private:
	friend class Singleton;

	TileManager();
	~TileManager();

public:
	void Render();
	void Update();

	void SetMap(string mapNameStr) { this->mapNameStr = mapNameStr; }

	void SetBGTile(vector<vector<Tile*>> bgTiles) { this->bgTiles = bgTiles; }
	vector<vector<Tile*>> GetBGTiles() { return bgTiles; }

	Tile::Type GetIdxBgTileType(Vector2 idx) { return bgTiles[idx.x][idx.y]->GetType(); }
	void SetIdxBgTileType(Vector2 idx,Tile::Type type) { bgTiles[idx.x][idx.y]->SetType(type); }
	Tile* GetBgTile(Vector2 idx) {return bgTiles[idx.x][idx.y];}

	void CreateBGTile();
	void LoadMapData(string file);
	void LoadMapSize();
	void LoadGameMap() { LoadMapData(PATH + mapNameStr + ".map"); LoadMapSize(); }
	void LoadMonster();

	void ClearObjTile();
	void AddObjTile(const Vector2& pos, const Vector2& size, const Vector2 idx, const wstring textureFile);
	void PopObjTile();

	Tile* GetNearPosTileState(GameObject* target, Tile::Type type = Tile::BASIC);
	Tile* GetNearPosTileState(Vector2 pos);

	void PushPlayer(Character* player);
	void CheckMapPosPlayer(Character* player);

public:
	map<string, float> mapSize;

	GameObject* tiles;
	vector<vector<Tile*>> bgTiles;
	vector<ObstacleTile*> objTiles;

	vector<GameObject*> gameObjects;

	string mapNameStr="Map1";

	Vector2 tileSize;
};