#pragma once

class EditTileMap : public Transform
{
public:
    EditTileMap(UINT size);
    ~EditTileMap();

    void Update();
    void Render();
    void RenderSampleButtons();

    void UpdateWorld() override;    
private:
    void CreateBGTile();
    void CreateSampleButtons();        

    void AddObjTile(const Vector2& pos);
    void RemoveObjTile(const Vector2& pos);

    void Save();
    void Load();

    void SaveMapData(string file);
    void LoadMapData(string file);

    void ClearObjTile();

private:
    UINT size;
    Vector2 tileSize;
    wstring selectTextureFile;

    vector<Tile*> bgTiles;
    vector<Tile*> objTiles;
    vector<Texture*> sampleTextures;

    int type;
};