#include "Framework.h"

TileManager::TileManager(): Quad()
{
    SetTag("TileManager");

    CreateBGTile();
    Load();
    LoadMapData(PATH + mapNameStr+ ".map");

}

TileManager::~TileManager()
{
}

void TileManager::PreRender()
{
    for (UINT y = 0; y < SIZEY; y++)
    {
        for (UINT x = 0; x < SIZEX; x++)
        {
            Tile* tile = bgTiles[x][y];
            tile->Render();
        }
    }
}

void TileManager::Render()
{
    RenderManager::Get()->Render("BG");
    RenderManager::Get()->Render("GameObject");
}

void TileManager::PostRender()
{
    for (UINT y = 0; y < SIZEY; y++)
    {
        for (UINT x = 0; x < SIZEX; x++)
        {
            Tile* tile = bgTiles[x][y];
            tile->PostRender();
        }
    }
    


    for (Tile* tile : objTiles)
        tile->Render();
}

void TileManager::Update()
{
    for (UINT y = 0; y < SIZEY; y++)
    {
        for (UINT x = 0; x < SIZEX; x++)
        {
            Tile* tile = bgTiles[x][y];
            if (tile->GetType() == Tile::PLAYER)
            {
                for (GameObject* gameObj : gameObjects)
                {
                    if (tile->GetGlobalPosition().y > gameObj->GetGlobalPosition().y)
                    {
                       // gameObj->SetDepth(-1);
                    }
                    else 
                    {
                     //   gameObj->SetDepth(10);
                    }
                }
            }
            tile->UpdateWorld();
        }
    }
        
    for (Tile* tile : objTiles)
        tile->UpdateWorld();



    UpdateWorld();
}

void TileManager::CreateBGTile()
{
    wstring baseFile = L"ResourcesCA/Textures/Tiles/Basic/Tile (1).png";
    Texture* baseTile = Texture::Add(baseFile);
    tileSize = baseTile->GetSize();

    bgTiles.resize(SIZEX);

    // 각 행 벡터를 초기화합니다.
    for (UINT y = 0; y < SIZEX; y++) {
        // 각 행 벡터를 추가합니다.
        // 각 행 벡터의 용량을 sizeX만큼 예약합니다.
        bgTiles[y].resize(SIZEY);
    }


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
            tile->SetParent(this);
            tile->SetCurIdx(Vector2{ (float)x,(float)y });
            bgTiles[x][y] = tile;
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
        bgTiles[size / SIZEX][size % SIZEX]->SetTexture(reader->WString());
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
        tile->SetParent(this);
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

//void TileManager::SetNearPosState( RectCollider* target, Tile::Type type)
//{
//    for (Tile* tile : bgTiles)
//    {
//        if (tile->GetCollider()->IsRectCollision(target, nullptr))
//        {
//            tile->SetType(type);
//        }
//    }
//}

Tile* TileManager::SetNearPosState(GameObject* target, Tile::Type type)
{
    float minDistance = Distance(bgTiles[0][0]->GetGlobalPosition(), target->GetGlobalPosition());
    Tile* minDistanceTile = nullptr;

    for (UINT y = 0; y < SIZEY; y++)
    {
        for (UINT x = 0; x < SIZEX; x++)
        {
            Tile* tile = bgTiles[x][y];
            tile->SetType(Tile::BASIC);

            float distance = Distance(tile->GetGlobalPosition(), target->GetGlobalPosition());

            if (distance < minDistance)
                //if (distance < minDistance tile->GetType() == Tile::BASIC)
            {
                minDistance = distance;
                minDistanceTile = tile;
            }
            
        }
    }
    if(minDistanceTile)
        minDistanceTile->SetType(type);

    if(type != Tile::PLAYER)
        RenderManager::Get()->Add("GameObject", target);
        

    return minDistanceTile;
}



Tile* TileManager::Collision(string key, Collider* collider)
{
    return nullptr;
}
