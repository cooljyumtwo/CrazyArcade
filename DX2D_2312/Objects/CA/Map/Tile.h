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
    Tile(Data data);
    ~Tile();

    void Render() override;
    void PostRender();

    void UpdateWorld() override;

    Data GetData() { return data; }
    RectCollider* GetCollider() { return collider; }

    static bool IsCompare(Tile* tile1, Tile* tile2);

private:
    Data data;

    RectCollider* collider;
};