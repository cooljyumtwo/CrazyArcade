#include "Framework.h"

FloorManager::FloorManager()
{
    background = new Quad(L"Resources/Textures/BG/bg.png", false);
    background->SetLocalPosition(CENTER);
    background->SetTag("BG");
  //  background->SetDepth(-10);
    background->Update();
}

FloorManager::~FloorManager()
{
    for (Floor* floor : floors)
        delete floor;
}

void FloorManager::Update()
{    
}

void FloorManager::Render()
{
    background->Render();

    for (Floor* floor : floors)
        floor->Render();

    //if (ImGui::TreeNode("Floor Editor"))
    //{
    //    if (ImGui::Button("Save"))
    //        Save();
    //
    //    ImGui::SameLine();
    //
    //    if (ImGui::Button("Load"))
    //        Load();
    //
    //    ImGui::TreePop();
    //}    
}

void FloorManager::Add(const Vector2& pos, wstring textureFile)
{
    for (Floor* floor : floors)
    {
        if (floor->GetCollider()->IsPointCollision(pos))
        {
            return;
        }
    }

    Floor* floor = new Floor(textureFile);
    floor->SetLocalPosition(pos);
    floor->Update();

    floors.push_back(floor);
}

void FloorManager::Remove()
{
    FOR(floors.size())
    {
        if (floors[i]->GetCollider()->IsPointCollision(mousePos))
        {
            floors.erase(floors.begin() + i);
            return;
        }
    }
}

void FloorManager::Save()
{
    SaveBG();

    BinaryWriter* writer = new BinaryWriter("Resources/TextData/Map/Floor.data");
    writer->UInt(floors.size());

    for (Floor* floor : floors)
    {
        writer->Vector(floor->GetGlobalPosition());
        writer->WString(floor->GetMaterial()->GetTexture()->GetFile());
    }

    delete writer;
}

void FloorManager::SaveBG()
{
    background->Save();

    BinaryWriter* writer = new BinaryWriter("Resources/TextData/Map/BG.data");
    writer->WString(background->GetMaterial()->GetTexture()->GetFile());
    delete writer;
}

void FloorManager::LoadBG()
{
    background->Load();

    BinaryReader* reader = new BinaryReader("Resources/TextData/Map/BG.data");

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    background->SetTexture(reader->WString());
    delete reader;
}

void FloorManager::Load()
{
    LoadBG();

    BinaryReader* reader = new BinaryReader("Resources/TextData/Map/Floor.data");
    UINT size = reader->UInt();

    floors.reserve(size);

    FOR(size)
    {
        Vector2 pos = reader->Vector();
        wstring file = reader->WString();

        Add(pos, file);
    }

    delete reader;
}

Collider* FloorManager::Collision(Collider* collider)
{
    for (Floor* floor : floors)
    {
        if (floor->GetCollider()->IsCollision(collider))
            return floor->GetCollider();
    }

    return nullptr;
}
