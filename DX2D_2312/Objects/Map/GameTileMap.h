#pragma once

class GameTileMap : public Transform
{
public:
    GameTileMap(string dataFile);
    ~GameTileMap();

    void Render();

private:
    void CreateBGTile();    

    void Load(string file);

private:
    UINT size;

    Vector2 tileSize;

    vector<Tile*> bgTiles;
    vector<Tile*> objTiles;
};