#pragma once

class Tile : public Quad
{
public:
    enum Type
    {
        BASIC, OBSTACLE , ATTACK
    };

public:
    static float TILE_SIZE;

public:
    Tile( wstring textureFile, Vector2 pos, Type type = BASIC);
    ~Tile();

    void Render() override;
    void PostRender();

    void UpdateWorld() override;

    static bool IsCompare(Tile* tile1, Tile* tile2);

    void SetType(Type changeType) { this->type = changeType; }
    Type GetType() { return type; }

    void SetTileObj(TileObject* tileObj) { this->tileObj = tileObj; }

    void SetCurIdx(Vector2 curIdx) { this->curIdx = curIdx; }
    Vector2 GetCurIdx() { return curIdx; }

    float GetDepth() override;
   
protected:
    Vector2 curIdx;

    Type type = BASIC;

    TileObject* tileObj = nullptr;
};