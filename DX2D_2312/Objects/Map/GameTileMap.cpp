#include "Framework.h"

GameTileMap::GameTileMap(string dataFile)
{    
    SetLocalPosition(CENTER);
    UpdateWorld();

    Load(dataFile);
}

GameTileMap::~GameTileMap()
{
}

void GameTileMap::Render()
{
    for (Tile* tile : bgTiles)
        tile->Render();    

    for (Tile* tile : objTiles)
        tile->Render();
}

void GameTileMap::CreateBGTile()
{
    wstring baseFile = L"Resources/Textures/Tiles/voxelTile_05.png";
    Texture* baseTile = Texture::Add(baseFile);
    tileSize = baseTile->GetSize();

    bgTiles.reserve(size * size);

    Vector2 startPos = { 0, size * 0.5f * tileSize.y * 0.5f };

    for (UINT y = 0; y < size; y++)
    {
        for (UINT x = 0; x < size; x++)
        {
            Tile::Data data = {};
            data.textureFile = baseFile;
            Vector2 xDirection = Vector2(tileSize.x, -tileSize.y * 0.5f) * 0.5f;
            Vector2 yDirection = Vector2(-tileSize.x, -tileSize.y * 0.5f) * 0.5f;

            data.pos = startPos + xDirection * x + yDirection * y;

            Tile* tile = new Tile(data);
            tile->SetParent(this);
            tile->Update();
            bgTiles.push_back(tile);
        }
    }
}

void GameTileMap::Load(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    UINT size = reader->UInt();

    this->size = sqrt(size);
    CreateBGTile();

    FOR(size)
    {
        bgTiles[i]->SetTexture(reader->WString());
    }

    size = reader->UInt();

    FOR(size)
    {
        Tile::Data data = {};
        data.textureFile = reader->WString();
        data.pos = reader->Vector();
        data.type = Tile::OBJ;

        Tile* tile = new Tile(data);
        tile->SetParent(this);
        tile->Update();

        objTiles.push_back(tile);
    }

    sort(objTiles.begin(), objTiles.end(), &Tile::IsCompare);

    delete reader;
}
