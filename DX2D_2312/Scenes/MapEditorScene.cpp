#include "Framework.h"
#include "MapEditorScene.h"

MapEditorScene::MapEditorScene()
{
    sampleTile = new Quad(L"Resources/Textures/BG/Floor.png");
    t = new TileObject();
    TileObjectManager::Get();
}

MapEditorScene::~MapEditorScene()
{
    FloorManager::Delete();
}

void MapEditorScene::Update()
{
    int x = (int)mousePos.x / CELL_WIDTH;
    int y = (int)mousePos.y / CELL_HEIGHT;
    
    Vector2 halfSize = Vector2(CELL_WIDTH * 0.5f, CELL_HEIGHT * 0.5f);
    Vector2 pos = Vector2(x, y) * Vector2(CELL_WIDTH, CELL_HEIGHT) + halfSize;

    sampleTile->SetLocalPosition(pos);

    if (!ImGui::GetIO().WantCaptureMouse && KEY->Down(VK_LBUTTON))
    {
        FloorManager::Get()->Add(pos, sampleTile->GetMaterial()->GetTexture()->GetFile());
    }

    if (!ImGui::GetIO().WantCaptureMouse && KEY->Down(VK_RBUTTON))
    {
        FloorManager::Get()->Remove();
    }
    t->Update();
}

void MapEditorScene::Render()
{
    FloorManager::Get()->Render();

    t->Render();
}

void MapEditorScene::PostRender()
{
    EditBG();
    EditTexture(sampleTile, "Tile");
}

void MapEditorScene::EditBG()
{
    EditTexture(FloorManager::Get()->GetBG(), "BG");

    FloorManager::Get()->GetBG()->RenderUI();
}

void MapEditorScene::EditTexture(Quad* quad, string key)
{
    if (ImGui::Button(key.c_str()))
        DIALOG->OpenDialog(key, key, ".png,.jpg");

    if (DIALOG->Display(key))
    {
        if (DIALOG->IsOk())
        {
            string path = "Resources/Textures/BG/";
            string file = DIALOG->GetCurrentFileName();

            quad->SetTexture(ToWString(path + file));
        }

        DIALOG->Close();
    }
}
