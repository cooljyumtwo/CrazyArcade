#include "Framework.h"
#include "MapEditScene.h"

MapEditScene::MapEditScene()
{
    CAM->SetFix(false);

    tileMap = new EditTileMap(15, 13);
    tileMap->UpdateWorld();
}

MapEditScene::~MapEditScene()
{
    delete tileMap;
}

void MapEditScene::Update()
{
    tileMap->Update();
    tileMap->UpdateWorld();
}

void MapEditScene::Render()
{
    tileMap->Render();
}

void MapEditScene::PostRender()
{
    tileMap->RenderSampleButtons();
}
