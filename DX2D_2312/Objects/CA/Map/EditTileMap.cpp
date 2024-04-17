#include "Framework.h"

EditTileMap::EditTileMap()
{
    SetTag("EditTileMap");

    CreateBGTile();
    CreateSampleButtons();

    Transform::Load();

    UpdateWorld();
}

EditTileMap::~EditTileMap()
{
    for (UINT y = 0; y < sizeY; y++)
    {
        for (UINT x = 0; x < sizeX; x++)
        {
            delete bgTiles[x][y];
        }
    }
}

void EditTileMap::Render()
{
    for (UINT y = 0; y < sizeY; y++)
    {
        for (UINT x = 0; x < sizeX; x++)
        {
            bgTiles[x][y]->Render();
        }
    }

    sort(objTiles.begin(), objTiles.end(), &Tile::IsCompare);

    for (ObstacleTile* tile : objTiles)
        tile->Render();

    for (UINT y = 0; y < sizeY; y++)
    {
        for (UINT x = 0; x < sizeX; x++)
        {
           bgTiles[x][y]->PostRender();
        }
    }

    //ImGui
    const char* list[] = {"BASIC", "OBSTACLE"};
    if (ImGui::Combo("Type", &type, list, 2)) 
    {
        SetType();
    }

    if (ImGui::TreeNode((tag + "EditTileMap_Transform").c_str()))
    {
        //ImGui::DragFloat2("Pos", (float*)&localPosition, 1.0f);

        Save();
        ImGui::SameLine();
        Load();

        ImGui::TreePop();
    }

    ImGui::DragFloat2("Pos", (float*)&localPosition, 1.0f);
    if (ImGui::Button("S"))
        Transform::Save();
    if (ImGui::Button("L"))
        Transform::Load();
}

void EditTileMap::Update()
{
    Vector2 pos = CAM->ScreenToWorld(mousePos);

    CheckAddObjTile(pos);

    if (KEY->Down(VK_RBUTTON))
        RemoveObjTile(pos);
}

void EditTileMap::UpdateWorld()
{
    Transform::UpdateWorld();

    for (UINT y = 0; y < sizeY; y++)
    {
        for (UINT x = 0; x < sizeX; x++)
        {
            bgTiles[x][y]->UpdateWorld();
        }
    }

    for (ObstacleTile* tile : objTiles)
        tile->UpdateWorld();
}

void EditTileMap::RenderSampleButtons()
{
    UINT width = 5;

    if (ImGui::TreeNode("Sample Buttons"))
    {
        int count = 0;

        for (Texture* texture : sampleTextures)
        {
            if (ImGui::ImageButton(texture->GetSRV(), ImVec2(50, 50)))
            {
                selectTextureFile = texture->GetFile();
            }

            count++;

            if (count % 5)
                ImGui::SameLine();
        }

        ImGui::TreePop();
    }
}

void EditTileMap::CreateBGTile()
{
    bgTiles = TileManager::Get()->GetBGTile();

    sizeX = bgTiles.size();
    sizeY = bgTiles[0].size();
    
    for (UINT y = 0; y < sizeY; y++)
    {
        for (UINT x = 0; x < sizeX; x++)
        {
            Tile* tile = bgTiles[x][y];
            tile->SetParent(this);
        }
    }

    tileSize = bgTiles[0][0]->GetSize();
}

void EditTileMap::CreateSampleButtons()
{
    WIN32_FIND_DATA findData;

    wstring typePath = L"ResourcesCA/Textures/Tiles/";
    switch (type)
    {
    case 0:
        typePath += L"Basic/";
        break;
    case 1:
        typePath += L"Obstacle/";
        break;
    default:
        break;
    }

    HANDLE handle = FindFirstFile( (typePath + L"*.png").c_str(), &findData);

    bool result = true;
    wstring path =  typePath;

    sampleTextures.clear();
    while (result)
    {
        Texture* texture = Texture::Add(path + findData.cFileName);

        sampleTextures.push_back(texture);

        result = FindNextFile(handle, &findData);
    }
}

void EditTileMap::SetType()
{
    CreateSampleButtons();
}

void EditTileMap::Save()
{
    string key = "SaveEditTile";
    string path = "ResourcesCA/TextData/Map/";

    if (ImGui::Button(key.c_str()))
        DIALOG->OpenDialog(key, path, ".map");

    if (DIALOG->Display(key))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetCurrentFileName();

            SaveMapData(path + file);
        }

        DIALOG->Close();
    }
}

void EditTileMap::Load()
{
    string key = "LoadEditTile";

    if (ImGui::Button(key.c_str()))
        DIALOG->OpenDialog(key, key, ".map");

    if (DIALOG->Display(key))
    {
        if (DIALOG->IsOk())
        {
            string path = "ResourcesCA/TextData/Map/";
            string file = DIALOG->GetCurrentFileName();

            LoadMapData(path + file);
        }

        DIALOG->Close();
    }
}

void EditTileMap::SaveMapData(string file)
{
    BinaryWriter* writer = new BinaryWriter(file);
    
    writer->UInt(sizeX);
    writer->UInt(sizeY);

    for (UINT y = 0; y < sizeY; y++)
    {
        for (UINT x = 0; x < sizeX; x++)
        {
            Tile* tile = bgTiles[x][y];
            writer->WString(tile->GetMaterial()->GetTexture()->GetFile());
        }
    }

    writer->UInt(objTiles.size());

    for (ObstacleTile* tile : objTiles)
    {
        writer->WString(tile->GetData().textureFile);
        writer->Vector(tile->GetData().pos);
        writer->Vector(tile->GetCurIdx());
    }

    delete writer;
}

void EditTileMap::LoadMapData(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    UINT SIZE_X = reader->UInt();
    UINT SIZE_Y = reader->UInt();

    FOR_Y(SIZE_Y){
        FOR_X(SIZE_X)
        {
            bgTiles[x][y]->SetTexture(reader->WString());
        }
    }

    int size = reader->UInt();

    ClearObjTile();

    FOR(size)
    {
        Tile::Data data = {};
        data.textureFile = reader->WString();
        data.pos = reader->Vector();
        Vector2 curIdx = reader->Vector();

        selectTextureFile = data.textureFile;
        AddObjTile(data.pos, tileSize, curIdx);
    }

    delete reader;
}

void EditTileMap::ClearObjTile()
{
    for (ObstacleTile* tile : objTiles)
        delete tile;

    objTiles.clear();
}

void EditTileMap::CheckAddObjTile(Vector2 pos)
{
    for (UINT y = 0; y < sizeY; y++)
    {
        for (UINT x = 0; x < sizeX; x++)
        {
            Tile* tile = bgTiles[x][y];

            if (tile->GetCollider()->IsPointCollision(pos))
            {
                tile->GetMaterial()->SetColor(0, 1.0f, 0);

                if (!ImGui::GetIO().WantCaptureMouse && selectTextureFile.size() != 0 && KEY->Press(VK_LBUTTON))
                {
                    if (type == 0)
                        tile->SetTexture(selectTextureFile);
                    else
                    {
                        Vector2 size = tile->GetSize();
                        AddObjTile(tile->GetLocalPosition(), tile->GetSize(), tile->GetCurIdx());
                        tile->SetType(Tile::OBSTACLE);
                    }
                }
            }
            else
            {
                tile->GetMaterial()->SetColor(1, 1, 1);
            }
        }
    }
}

void EditTileMap::AddObjTile(const Vector2& pos, const Vector2& size, const Vector2 idx)
{
    Tile::Data data = {};
    data.textureFile = selectTextureFile;
    data.pos = pos;
    // data.type = Tile::OBJ;    

    ObstacleTile* tile = new ObstacleTile(data);
    tile->SetParent(this);
    tile->Translate(Vector2::Up() * (tile->GetSize().y - size.y) * 0.5);
    tile->Update();
    tile->SetCurIdx(idx);
    bgTiles[idx.x][idx.y]->SetType(Tile::OBSTACLE);

    RemoveObjTile(tile->GetCollider()->GetGlobalPosition());

    objTiles.push_back(tile);
    tile->UpdateWorld();
}

void EditTileMap::RemoveObjTile(const Vector2& pos)
{

    vector<ObstacleTile*>::iterator iter = objTiles.begin();

    for (; iter != objTiles.end(); )
    {
        Tile* tile = *iter;

        if (tile->GetCollider()->IsPointCollision(pos))
        {
            int curIdxX = tile->GetCurIdx().x;
            int curIdxY = tile->GetCurIdx().y;
            bgTiles[curIdxX][curIdxY]->SetType(Tile::BASIC);
            delete tile;
            iter = objTiles.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}
