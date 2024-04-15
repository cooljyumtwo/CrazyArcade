#pragma once

class Tile : public Quad
{
public:

    enum Type
    {
        BASIC, OBSTACLE
    };

    struct Data
    {
        wstring textureFile;
        Vector2 pos;
        Type type = BASIC;
    };

public:
    static float TILE_SIZE;

public:
    Tile(Data data);
    ~Tile();

    void Render() override;
    void PostRender();

    void UpdateWorld() override;

    Data GetData() { return data; }
    RectCollider* GetCollider() { return collider; }

    static bool IsCompare(Tile* tile1, Tile* tile2);

    void SetType(Type type) { data.type = type; }

    void SetTileObj(TileObject* tileObj) { this->tileObj = tileObj; }

    void SetCurIdx(int curIdx) { this->curIdx = curIdx; }
    int GetCurIdx() { return curIdx; }
   

protected:
    Data data;

    RectCollider* collider;

    TileObject* tileObj = nullptr;

    int curIdx;
};