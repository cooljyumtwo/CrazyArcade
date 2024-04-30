#pragma once

class EditTileMap : public Transform 
{
public:
    EditTileMap();
    ~EditTileMap();

    void Render();
    void Update();
    void UpdateWorld() override;

    void RenderSampleButtons();

private:
    void CreateBGTile();
    void CreateSampleButtons();     
    void CreatePlayerTile();

    void SetPlayerPos(Vector2 curIdx);

    void SetType();

    void Save();
    void Load();

    void SaveMapData(string file);
    void LoadMapData(string file);

    void SaveMonster(string file);
    void LoadMonster(string file);

    void ClearObjTile();
    void CheckAddObjTile(Vector2 pos);
    void AddObjTile(const Vector2& pos, const Vector2& size, const Vector2& idx);
    void RemoveObjTile(const Vector2& pos);

    void ClearMonster();
    void AddMonster(const Vector2& pos, const Vector2& idx, wstring textureFile = L"");
    void RemoveMonster(const Vector2& pos , Collider* collider = nullptr);

private:
    int type = 0;

    bool isClick = false;

    UINT sizeX;
    UINT sizeY;

    Vector2 tileSize;
    wstring selectTextureFile;

    vector<vector<Tile*>> bgTiles;
    vector<ObstacleTile*> objTiles;
    vector<pair<Tile*,int>> monsterTiles;
    vector<Texture*> sampleTextures;

    Tile* playerPosTile;
};