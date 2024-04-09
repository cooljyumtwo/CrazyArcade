#include "Framework.h"
#include "StageScene.h"

StageScene::StageScene()
{
    CAM->SetFix(false);

    tileMap = new EditTileMap(15,13);
    tileMap->UpdateWorld();
}

StageScene::~StageScene()
{
    delete tileMap;
}

void StageScene::Update()
{
    tileMap->Update();
    tileMap->UpdateWorld();
}

void StageScene::Render()
{
    tileMap->Render();
}

void StageScene::PostRender()
{
    tileMap->RenderSampleButtons();
}
