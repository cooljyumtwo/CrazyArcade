#pragma once

class EditTileMap : public Transform
{
public:
    EditTileMap(UINT sizeX, UINT sizeY);
    ~EditTileMap();

    void Update();
    void PreRender();
    void Render();
    void PostRender();
    void RenderSampleButtons();

    void UpdateWorld() override;    

    void Save();
    void Load();
private:
    void CreateBGTile();
    void CreateSampleButtons();     

    void SetType();

    void AddObjTile(const Vector2& pos, const Vector2& size, const int idx);
    void RemoveObjTile(const Vector2& pos);


    void SaveMapData(string file);
    void LoadMapData(string file);

    void ClearObjTile();

private:
    UINT sizeX;
    UINT sizeY;
    Vector2 tileSize;
    wstring selectTextureFile;

    vector<Tile*> bgTiles;
    vector<ObstacleTile*> objTiles;
    vector<Texture*> sampleTextures;

    int type = 0;
};