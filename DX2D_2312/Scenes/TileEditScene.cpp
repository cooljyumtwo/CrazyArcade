#include "Framework.h"
#include "TileEditScene.h"

TileEditScene::TileEditScene()
{
    CAM->SetFix(false);

    tileMap = new EditTileMap(15,13);    
    tileMap->UpdateWorld();
}

TileEditScene::~TileEditScene()
{
    delete tileMap;
}

void TileEditScene::Update()
{
    tileMap->Update();
}

void TileEditScene::Render()
{
    tileMap->Render();
}

void TileEditScene::PostRender()
{
    tileMap->RenderSampleButtons();
}