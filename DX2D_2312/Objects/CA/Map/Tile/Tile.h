#pragma once

class Tile : public Quad
{
public:

    enum Type
    {
        BASIC, OBSTACLE , ATTACK
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
    Type GetType() { return data.type; }

    void SetTileObj(TileObject* tileObj) { this->tileObj = tileObj; }

    void SetCurIdx(Vector2 curIdx) { this->curIdx = curIdx; }
    Vector2 GetCurIdx() { return curIdx; }

    float GetDepth() override;
   

protected:
    Data data;

    RectCollider* collider;

    TileObject* tileObj = nullptr;

    Vector2 curIdx;
};