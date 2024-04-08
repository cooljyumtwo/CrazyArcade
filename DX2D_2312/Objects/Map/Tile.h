#pragma once

class Tile : public Quad
{
public:
    enum Type
    {
        BG, OBJ
    };

    struct Data
    {
        wstring textureFile;
        Vector2 pos;
        Type type = BG;
    };

public:
    Tile(Data data);
    ~Tile();

    void Render() override;
    void PostRender();

    void UpdateWorld() override;

    Data GetData() { return data; }
    IsometricCollider* GetCollider() { return collider; }

    static bool IsCompare(Tile* tile1, Tile* tile2);

private:
    Data data;

    IsometricCollider* collider;
};