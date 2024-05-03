#pragma once

class TileManager : public Singleton<TileManager>, Transform
{
public:
	UINT SIZE_X = 15;
	UINT SIZE_Y = 13;

private:
	string PATH = "ResourcesCA/TextData/Map/";
	float OFFSET = 10.0f;
	float OFFSET_MAP_SIZE_UP = 5.0f;

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

	float GetMapsize(string key) { return mapSize[key]; }

	void CreateBGTile();
	void LoadMapData();
	void LoadMapSize();

	void CreateRanderTarget();
	void SetRanderTarget();

	void SetMapName(string mapNameStr) {this->mapNameStr= mapNameStr;}

	void ClearObjTile();
	void AddObjTile(const Vector2& pos, const Vector2& size, const Vector2 idx, const wstring textureFile);
	void PopObjTile();

	Tile* GetNearPosTileState(GameObject* target, Tile::Type type = Tile::BASIC);
	Tile* GetNearPosTileState(Vector2 pos);

	bool PushGameObject(GameObject* player);
	bool CheckMapPosPlayer(Character* player);

public:
	map<string, float> mapSize;

	GameObject* tiles;
	vector<vector<Tile*>> bgTiles;
	vector<ObstacleTile*> objTiles;

	vector<GameObject*> gameObjects;

	Vector2 tileSize;

	static string mapNameStr;

	RenderTarget* bgTileTarget;
	Quad* bgTileMap;
};