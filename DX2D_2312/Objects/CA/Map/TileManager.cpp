#include "Framework.h"

TileManager::TileManager()
{
    CreateBGTile();
    LoadMapData(PATH + mapNameStr+ ".map");
}

TileManager::~TileManager()
{
}

void TileManager::Render()
{
    for (Tile* tile : bgTiles)
    {
        tile->Render();
        tile->PostRender();

    }
        

    for (Tile* tile : objTiles)
        tile->Render();

}

void TileManager::Update()
{
    for (Tile* tile : bgTiles)
        tile->UpdateWorld();

    for (Tile* tile : objTiles)
        tile->UpdateWorld();
}

void TileManager::CreateBGTile()
{
    wstring baseFile = L"ResourcesCA/Textures/Tiles/Basic/Tile (1).png";
    Texture* baseTile = Texture::Add(baseFile);
    tileSize = baseTile->GetSize();

    bgTiles.reserve(SIZEX * SIZEX);

    Vector2 startPos = { 0, SIZEX * 0.5f * tileSize.y * 0.5f };

    for (UINT y = 0; y < SIZEY; y++)
    {
        for (UINT x = 0; x < SIZEX; x++)
        {
            BasicTile::Data data = {};
            data.textureFile = baseFile;
            Vector2 xDirection = Vector2(tileSize.x, 0);
            Vector2 yDirection = Vector2(0, -tileSize.y);

            data.pos = startPos + xDirection * x + yDirection * y;

            BasicTile* tile = new BasicTile(data);
          //  tile->SetParent(this);
            tile->SetCurIdx(bgTiles.size());
            bgTiles.push_back(tile);
        }
    }
}

void TileManager::LoadMapData(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    UINT size = reader->UInt();

    FOR(size)
    {
        bgTiles[i]->SetTexture(reader->WString());
    }

    size = reader->UInt();

    ClearObjTile();

    FOR(size)
    {
        Tile::Data data = {};
        data.textureFile = reader->WString();
        data.pos = reader->Vector();
        //  data.type = Tile::OBJ;

        ObstacleTile* tile = new ObstacleTile(data);
       // tile->SetParent(this);
        tile->Update();

        objTiles.push_back(tile);
    }

    delete reader;

}

void TileManager::ClearObjTile()
{
    for (ObstacleTile* tile : objTiles)
        delete tile;

    objTiles.clear();

}

void TileManager::SetNearPosState( RectCollider* target, Tile::Type type)
{
    for (Tile* tile : bgTiles)
    {
        if (tile->GetCollider()->IsRectCollision(target, nullptr))
        {
            tile->SetType(type);
        }
    }

}

Tile* TileManager::SetNearPosState(RectCollider* target)
{
    for (Tile* tile : bgTiles)
    {
        if (tile->GetCollider()->IsRectCollision(target, nullptr))
        {
            return tile;
        }
    }
    return nullptr;
}

Tile* TileManager::Collision(string key, Collider* collider)
{
    return nullptr;
}
