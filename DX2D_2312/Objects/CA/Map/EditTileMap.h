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

    void SetType();

    void Save();
    void Load();

    void SaveMapData(string file);
    void LoadMapData(string file);

    void ClearObjTile();
    void CheckAddObjTile(Vector2 pos);
    void AddObjTile(const Vector2& pos, const Vector2& size, const Vector2 idx);
    void RemoveObjTile(const Vector2& pos);

private:
    int type = 0;

    UINT sizeX;
    UINT sizeY;

    Vector2 tileSize;
    wstring selectTextureFile;

    vector<vector<Tile*>> bgTiles;
    vector<ObstacleTile*> objTiles;
    vector<Texture*> sampleTextures;
};