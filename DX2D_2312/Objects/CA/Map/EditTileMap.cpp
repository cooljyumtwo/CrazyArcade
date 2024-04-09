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
                    AddObjTile(tile->GetLocalPosition());
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

void EditTileMap::Render()
{
    for (Tile* tile : bgTiles)
        tile->Render();

    sort(objTiles.begin(), objTiles.end(), &Tile::IsCompare);

    for (Tile* tile : objTiles)
        tile->Render();

    for (Tile* tile : bgTiles)
        tile->PostRender();

    const char* list[] = {"BG", "OBJ"};
    ImGui::Combo("Type", &type, list, 2);

   // Save();
  //  ImGui::SameLine();
   // Load();

    Transform::RenderUI();
  
}

void EditTileMap::UpdateWorld()
{
    Transform::UpdateWorld();

    for (Tile* tile : bgTiles)
        tile->UpdateWorld();

    for (Tile* tile : objTiles)
        tile->UpdateWorld();
}

void EditTileMap::CreateBGTile()
{
    wstring baseFile = L"ResourcesCA/Textures/Tiles/Tile.png";
    Texture* baseTile = Texture::Add(baseFile);
    tileSize = baseTile->GetSize();

    bgTiles.reserve(sizeX * sizeX);

    Vector2 startPos = { 0, sizeX * 0.5f * tileSize.y * 0.5f };

    for (UINT y = 0; y < sizeY; y++)
    {
        for (UINT x = 0; x < sizeX; x++)
        {
            Tile::Data data = {};
            data.textureFile = baseFile;
            Vector2 xDirection = Vector2(tileSize.x, 0 );
            Vector2 yDirection = Vector2(0, -tileSize.y ) ;

            data.pos = startPos + xDirection * x + yDirection * y;

            Tile* tile = new Tile(data);
            tile->SetParent(this);
            bgTiles.push_back(tile);
        }
    }
}

void EditTileMap::CreateSampleButtons()
{
    WIN32_FIND_DATA findData;

    HANDLE handle = FindFirstFile(L"ResourcesCA/Textures/Tiles/*.png", &findData);

    bool result = true;
    wstring path = L"ResourcesCA/Textures/Tiles/";

    while (result)
    {
        Texture* texture = Texture::Add(path + findData.cFileName);

        sampleTextures.push_back(texture);

        result = FindNextFile(handle, &findData);
    }
}

void EditTileMap::AddObjTile(const Vector2& pos)
{
    Tile::Data data = {};
    data.textureFile = selectTextureFile;    
    data.pos = pos + Vector2::Up() * tileSize.y * 0.5f;
   // data.type = Tile::OBJ;    

    Tile* tile = new Tile(data);
    tile->SetParent(this);
    tile->Update();

    RemoveObjTile(tile->GetCollider()->GetGlobalPosition());

    objTiles.push_back(tile);
}

void EditTileMap::RemoveObjTile(const Vector2& pos)
{
    vector<Tile*>::iterator iter = objTiles.begin();

    for (; iter != objTiles.end() ; )
    {
        Tile* tile = *iter;

        if (tile->GetCollider()->IsPointCollision(pos))
        {
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
    string key = "Save";

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
    string key = "Load";

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

    for (Tile* tile : objTiles)
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

        Tile* tile = new Tile(data);
        tile->SetParent(this);
        tile->Update();        

        objTiles.push_back(tile);
    }

    delete reader;
}

void EditTileMap::ClearObjTile()
{
    for (Tile* tile : objTiles)
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
