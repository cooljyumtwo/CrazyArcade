#pragma once

class EditTileMap : public Transform
{
public:
    EditTileMap(UINT sizeX, UINT sizeY);
    ~EditTileMap();

    void Update();
    void Render();
    void RenderSampleButtons();

    void UpdateWorld() override;    
private:
    void CreateBGTile();
    void CreateSampleButtons();     

    void SetType();

    void AddObjTile(const Vector2& pos);
    void RemoveObjTile(const Vector2& pos);

    void Save();
    void Load();

    void SaveMapData(string file);
    void LoadMapData(string file);

    void ClearObjTile();

private:
    UINT sizeX;
    UINT sizeY;
    Vector2 tileSize;
    wstring selectTextureFile;

    vector<Tile*> bgTiles;
    vector<Tile*> objTiles;
    vector<Texture*> sampleTextures;

    int type = 0;
};