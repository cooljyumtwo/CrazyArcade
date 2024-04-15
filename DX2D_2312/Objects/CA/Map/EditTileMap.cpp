#include "Framework.h"

EditTileMap::EditTileMap(UINT sizeX, UINT sizeY)
    : sizeX(sizeX), sizeY(sizeY)
{
    SetTag("EditTileMap");
    CreateBGTile();

    Vector2 mapPos = CENTER;
    mapPos.x = tileSize.x * sizeX ;

    SetLocalPosition(mapPos);

    CreateSampleButtons();

    Transform::Load();
}

EditTileMap::~EditTileMap()
{
    for (Tile* tile : bgTiles)
        delete tile;
}

void EditTileMap::Update()
{
    Vector2 pos = CAM->ScreenToWorld(mousePos);

    for (Tile* tile : bgTiles)
    {
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

    if (KEY->Down(VK_RBUTTON))
        RemoveObjTile(pos);
}

void EditTileMap::PreRender()
{
    for (Tile* tile : bgTiles)
        tile->Render();
}

void EditTileMap::Render()
{

    sort(objTiles.begin(), objTiles.end(), &Tile::IsCompare);

    for (ObstacleTile* tile : objTiles)
        tile->Render();

    const char* list[] = {"BASIC", "OBSTACLE"};
    if (ImGui::Combo("Type", &type, list, 2)) 
    {
        SetType();
    }

    if (ImGui::TreeNode((tag + "EditTileMap_Transform").c_str()))
    {
        ImGui::DragFloat2("Pos", (float*)&localPosition, 1.0f);

        Save();
        ImGui::SameLine();
        Load();

        ImGui::TreePop();
    }
}

void EditTileMap::PostRender()
{
    for (Tile* tile : bgTiles)
        tile->PostRender();
}

void EditTileMap::UpdateWorld()
{
    Transform::UpdateWorld();

    for (Tile* tile : bgTiles)
        tile->UpdateWorld();

    //for (ObstacleTile* tile : objTiles)
    //    tile->UpdateWorld();
}

void EditTileMap::CreateBGTile()
{
    wstring baseFile = L"ResourcesCA/Textures/Tiles/Basic/Tile (1).png";
    Texture* baseTile = Texture::Add(baseFile);
    tileSize = baseTile->GetSize();

    bgTiles.reserve(sizeX * sizeX);

    Vector2 startPos = { 0, sizeX * 0.5f * tileSize.y * 0.5f };

    for (UINT y = 0; y < sizeY; y++)
    {
        for (UINT x = 0; x < sizeX; x++)
        {
            BasicTile::Data data = {};
            data.textureFile = baseFile;
            Vector2 xDirection = Vector2(tileSize.x, 0);
            Vector2 yDirection = Vector2(0, -tileSize.y);

            data.pos = startPos + xDirection * x + yDirection * y;

            BasicTile* tile = new BasicTile(data);
            tile->SetParent(this);
            tile->SetCurIdx(bgTiles.size());
            bgTiles.push_back(tile);
        }
    }
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

void EditTileMap::AddObjTile(const Vector2& pos, const Vector2& size, const int idx)
{
    Tile::Data data = {};
    data.textureFile = selectTextureFile;    
    data.pos = pos;
   // data.type = Tile::OBJ;    

    ObstacleTile* tile = new ObstacleTile(data);
    tile->SetParent(this);
    tile->Translate(Vector2::Up() * (tile->GetSize().y - size.y)*0.5);
    tile->Update();
    tile->SetCurIdx(idx);

    RemoveObjTile(tile->GetCollider()->GetGlobalPosition());

    objTiles.push_back(tile);
    tile->UpdateWorld();

}

void EditTileMap::RemoveObjTile(const Vector2& pos)
{

    vector<ObstacleTile*>::iterator iter = objTiles.begin();

    for (; iter != objTiles.end() ; )
    {
        Tile* tile = *iter;

        if (tile->GetCollider()->IsPointCollision(pos))
        {
            bgTiles[tile->GetCurIdx()]->SetType(Tile::BASIC);
            delete tile;
            iter = objTiles.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

void EditTileMap::Save()
{
    string key = "SaveEditTile";

    if (ImGui::Button(key.c_str()))
        DIALOG->OpenDialog(key, key, ".map");

    if (DIALOG->Display(key))
    {
        if (DIALOG->IsOk())
        {
            string path = "ResourcesCA/TextData/Map/";
            string file = DIALOG->GetCurrentFileName();

            SaveMapData(path + file);
        }

        DIALOG->Close();
    }
    Transform::Save();
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

    Transform::Load();
}

void EditTileMap::SaveMapData(string file)
{
    BinaryWriter* writer = new BinaryWriter(file);
    
    writer->UInt(bgTiles.size());

    for (Tile* tile : bgTiles)
    {
        writer->WString(tile->GetMaterial()->GetTexture()->GetFile());
    }

    writer->UInt(objTiles.size());

    for (ObstacleTile* tile : objTiles)
    {
        writer->WString(tile->GetData().textureFile);
        writer->Vector(tile->GetData().pos);
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
        tile->SetParent(this);
        tile->Update();        

        objTiles.push_back(tile);
    }

    delete reader;
}

void EditTileMap::ClearObjTile()
{
    for (ObstacleTile* tile : objTiles)
        delete tile;

    objTiles.clear();
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
