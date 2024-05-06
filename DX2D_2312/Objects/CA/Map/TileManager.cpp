#include "Framework.h"

string TileManager::mapNameStr = "Map3";

TileManager::TileManager()
{
    SetTag("TileManager");

    CreateBGTile();
    CreateRanderTarget();

    Transform::Load(); 

    UpdateWorld();

    EffectManager::Get()->Add("RemoveObstacle", 50, L"RemoveEffect.png",
        Vector2(4, 1));
}

TileManager::~TileManager()
{
    delete bgTileTarget;
    delete bgTileMap;
}

void TileManager::Render()
{
    bgTileMap->RenderUI();
    RenderUI();
}

void TileManager::Update()
{
    bgTileMap->UpdateWorld();
    FOR_X(SIZE_X)
        FOR_Y(SIZE_Y)
            bgTiles[x][y]->UpdateWorld();
        
    for (Tile* tile : objTiles)
    {
        tile->Update();
        tile->UpdateWorld();
    }

    UpdateWorld();

    EffectManager::Get()->Update();

    if (KEY->Down('N'))
    {
        TileManager::Get()->SetMapName("Map1");
        TileManager::Get()->LoadMapData();

        MonsterManager::Get()->LoadMonster();
        MonsterManager::Get()->LoadBossMonster();
        MonsterManager::Get()->SetIsRoad();
    }

    if (KEY->Down('M'))
    {
        MonsterManager::Get()->SetIsRoad();
        MonsterManager::Get()->ClearMonster();
    }

}

void TileManager::CreateBGTile()
{
    wstring baseFile = L"ResourcesCA/Textures/Tiles/Basic/Tile (1).png";
    Texture* baseTile = Texture::Add(baseFile);
    tileSize = baseTile->GetSize();

    bgTiles.resize(SIZE_X);

    for (UINT y = 0; y < SIZE_X; y++) {
        bgTiles[y].resize(SIZE_Y);
    }

    Vector2 startPos = { 0, SIZE_X * 0.5f * tileSize.y * 0.5f };

    FOR_X(SIZE_X)
        FOR_Y(SIZE_Y)
        {
            wstring textureFile = baseFile;
            Vector2 xDirection = Vector2(tileSize.x, 0);
            Vector2 yDirection = Vector2(0, -tileSize.y);

            Vector2 pos = startPos + xDirection * x + yDirection * y;

            BasicTile* tile = new BasicTile(textureFile, pos);
            tile->SetParent(this);
            tile->SetCurIdx(Vector2{ (float)x,(float)y });
            bgTiles[x][y] = tile;

            RenderManager::Get()->Add("BGTile",tile);
            RenderManager::Get()->Add("BGTileTxt",tile);
        }
}

void TileManager::LoadMapData()
{
    BinaryReader* reader = new BinaryReader(PATH + mapNameStr + ".map");

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    UINT SIZE_X = reader->UInt();
    UINT SIZE_Y = reader->UInt();

    FOR_Y(SIZE_Y)
        FOR_X(SIZE_X)
        {
            bgTiles[x][y]->SetTexture(reader->WString());  
            bgTiles[x][y]->SetType(Tile::BASIC);
        }

    
    int size = reader->UInt();

    ClearObjTile();

    FOR(size)
    {
        wstring textureFile = reader->WString();
        Vector2 pos = reader->Vector();
        Vector2 curIdx = reader->Vector();

        AddObjTile(pos, tileSize, curIdx, textureFile);
    }

    delete reader;

    SetRanderTarget();
}

void TileManager::LoadMapSize()
{
    mapSize["Left"] = bgTiles[0][0]->GetGlobalPosition().x;
    mapSize["Right"] = bgTiles[SIZE_X - 1][0]->GetGlobalPosition().x + Tile::TILE_SIZE;
    mapSize["Up"] = bgTiles[0][0]->GetGlobalPosition().y - OFFSET_MAP_SIZE_UP;
    mapSize["Down"] = bgTiles[0][SIZE_Y - 1]->GetGlobalPosition().y - Tile::TILE_SIZE;
}

void TileManager::CreateRanderTarget()
{
    //최적화를 위한 RenderTarget
    bgTileTarget = new RenderTarget();

    Texture* targetTexture = Texture::Add(L"BGTileMap", bgTileTarget->GetSRV());

    //RenderTarget을 띄울 이미지
    bgTileMap = new Quad(Vector2{ SCREEN_WIDTH, SCREEN_HEIGHT });
    bgTileMap->GetMaterial()->SetTexture(targetTexture);
    bgTileMap->SetLocalPosition(CENTER);
    bgTileMap->UpdateWorld();

    RenderManager::Get()->Add("BGTileRander", bgTileMap);
}


void TileManager::SetRanderTarget()
{
    //렌더할 이미지 Set()
    bgTileTarget->Set();
    RenderManager::Get()->Render("BG");
    RenderManager::Get()->Render("BGTile");
}

void TileManager::ClearObjTile()
{
    for (ObstacleTile* tile : objTiles)
    {
        RenderManager::Get()->Remove("GameObject", tile);
        delete tile;
    }

    objTiles.clear();
}

void TileManager::AddObjTile(const Vector2& pos, const Vector2& size, const Vector2 idx, const wstring textureFile)
{
    //TileData
    size_t posStr = textureFile.find_last_of(L'/');
    wstring fileName = textureFile.substr(posStr + 1);

    size_t startPos = fileName.find_first_of(L"(");
    size_t endPos = fileName.find_first_of(L")");
    wstring numStr = fileName.substr(startPos + 1, endPos - startPos - 1);
    int num = stoi(numStr);

    TileData tileData = DataManager::Get()->GetTileData(num);

    //Create
    ObstacleTile* tile = new ObstacleTile(textureFile, pos, tileData.isPop, tileData.isPush);
    tile->SetParent(this);
    tile->GetCollider()->Translate(Vector2::Up() * (tile->GetSize().y - size.y) * 0.5 * -1);
    tile->Update();
    tile->SetCurIdx(idx);
    
    BasicTile* bgTile = (BasicTile*)bgTiles[idx.x][idx.y];
    bgTile->SetObstacleTile(tile);
    bgTile->SetType(Tile::OBSTACLE);

    objTiles.push_back(tile);
    tile->UpdateWorld();

    RenderManager::Get()->Add("GameObject", tile);
}

void TileManager::PopObjTile()
{
    for (Tile* objTile : objTiles)
    {
        Tile::Type tiletype = TileManager::Get()->GetIdxBgTileType(objTile->GetCurIdx());
        if (tiletype == Tile::ATTACK)
        {
            ObstacleTile* tile = (ObstacleTile*)objTile;
            tile->Deactivate();
        }
    }
}

Tile* TileManager::GetNearPosTileState(GameObject* target, Tile::Type type)
{
    float minDistance = Distance(bgTiles[0][0]->GetGlobalPosition(), target->GetGlobalPosition());
    Tile* minDistanceTile = nullptr;

    for (UINT y = 0; y < SIZE_Y; y++)
    {
        for (UINT x = 0; x < SIZE_X; x++)
        {
            Tile* tile = bgTiles[x][y];

            float distance = Distance(tile->GetGlobalPosition(), target->GetGlobalPosition());

            if (distance < minDistance)
            {
                minDistance = distance;
                minDistanceTile = tile;
            }
        }
    }

    if(minDistanceTile)
        minDistanceTile->SetType(type);

    RenderManager::Get()->Add("GameObject", target);  

    return minDistanceTile;
}

Tile* TileManager::GetNearPosTileState(Vector2 pos)
{
    // 만약 위치(pos)가 지도 범위를 벗어난다면 nullptr 반환
    if (pos.x < mapSize["Left"] || pos.x + Tile::TILE_SIZE > mapSize["Right"]
        || pos.y > mapSize["Up"] || pos.y - Tile::TILE_SIZE < mapSize["Down"])
        return nullptr;

    // 첫 번째 타일의 위치를 가져옴 //기준이 되는 Tile
    Vector2 firstTilePos = bgTiles[0][0]->GetGlobalPosition();

    // 타일 좌표계로 변환
    Vector2 calPos = { pos.x - firstTilePos.x, firstTilePos.y - pos.y };
    calPos /= Tile::TILE_SIZE;
    calPos = { round(calPos.x), round(calPos.y) };

    // 변환된 타일 좌표에 해당하는 타일 반환
    return bgTiles[calPos.x][calPos.y];
}


bool TileManager::PushGameObject(GameObject* obj, bool isPlayer)
{
    //AABB충돌
    for (Tile* objTile : objTiles)
    {
        Vector2 overlab; //겹치는 부분

        if (objTile->GetCollider()->IsCollision(obj->GetCollider(), &overlab))
        {
            ObstacleTile* obstacleTile = (ObstacleTile*)objTile;
            bool isPush = obstacleTile->GetIsPush();

            if (overlab.x < overlab.y) //좌우충돌
            {

                if (isPush)
                    if (obj->GetGlobalPosition().x > objTile->GetGlobalPosition().x) //왼쪽충돌
                        if (!isPush || !isPlayer)
                            obj->Translate(Vector2::Right() * overlab.x);
                        else
                        {
                            if (obstacleTile->GetCurIdx().x == 0) return true;
                            Vector2 pos = obstacleTile->GetLocalPosition();
                            Vector2 movePos = obstacleTile->GetLocalPosition() + (Vector2::Left() * Tile::TILE_SIZE);
                            obstacleTile->SetTargetPos(movePos);
                            obstacleTile->SetCurIdx(Vector2{ obstacleTile->GetCurIdx().x - 1 ,obstacleTile->GetCurIdx().y });
                        }
                else //오른쪽충돌
                    if (!isPush || !isPlayer)
                        obj->Translate(Vector2::Left() * overlab.x);
                    else
                    {
                        if (obstacleTile->GetCurIdx().x == TileManager::Get()->SIZE_X - 1) return true;

                        Vector2 pos = obstacleTile->GetLocalPosition();
                        Vector2 movePos = obstacleTile->GetLocalPosition() + (Vector2::Right() * Tile::TILE_SIZE);
                        obstacleTile->SetTargetPos(movePos);
                        obstacleTile->SetCurIdx(Vector2{ obstacleTile->GetCurIdx().x + 1,obstacleTile->GetCurIdx().y });

                    }
            }
            else //상하충돌
            {
                if (obj->GetGlobalPosition().y > objTile->GetGlobalPosition().y) //아래쪽충돌
                    if (!isPush || !isPlayer)
                        obj->Translate(Vector2::Up() * overlab.y);
                    else
                    {
                        if (obstacleTile->GetCurIdx().y == TileManager::Get()->SIZE_Y - 1) return true;
                        Vector2 pos = obstacleTile->GetLocalPosition();
                        Vector2 movePos = obstacleTile->GetLocalPosition() + (Vector2::Down() * Tile::TILE_SIZE);
                        obstacleTile->SetTargetPos(movePos);
                        obstacleTile->SetCurIdx(Vector2{ obstacleTile->GetCurIdx().x,obstacleTile->GetCurIdx().y + 1});

                    }
                else //위쪽충돌
                    if (!isPush || !isPlayer)
                        obj->Translate(Vector2::Down() * overlab.y);
                    else
                    {
                        if (obstacleTile->GetCurIdx().y == 0) return true;
                        Vector2 pos = obstacleTile->GetLocalPosition();
                        Vector2 movePos = obstacleTile->GetLocalPosition() + (Vector2::Up() * Tile::TILE_SIZE);
                        obstacleTile->SetTargetPos(movePos);
                        obstacleTile->SetCurIdx(Vector2{ obstacleTile->GetCurIdx().x,obstacleTile->GetCurIdx().y - 1 });

                    }
            }

            obj->UpdateWorld();
            return true;
        }
    }
    return false;
}

bool TileManager::CheckMapPosPlayer(Character* player)
{
    Vector2 pos = player->GetCollider()->GetGlobalPosition();

    float size = round(player->GetCollider()->Size().y / Tile::TILE_SIZE);

    if (pos.x < mapSize["Left"]) 
        player->Translate(Vector2::Right() * (mapSize["Left"] - pos.x));
    else if (pos.x + Tile::TILE_SIZE* size > mapSize["Right"])
        player->Translate(Vector2::Left() * ((pos.x + Tile::TILE_SIZE * size) - mapSize["Right"]));
    else if (pos.y > mapSize["Up"]) 
        player->Translate(Vector2::Down() * (pos.y - mapSize["Up"]));
    else if (pos.y - Tile::TILE_SIZE * size - OFFSET < mapSize["Down"])
        player->Translate(Vector2::Up() * (mapSize["Down"] - (pos.y - Tile::TILE_SIZE * size - OFFSET)));
    else 
        return false;

    return true;
}