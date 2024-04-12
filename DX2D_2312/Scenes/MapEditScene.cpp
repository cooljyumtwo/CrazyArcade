#include "Framework.h"
#include "MapEditScene.h"

MapEditScene::MapEditScene()
{
    CAM->SetFix(false);

    tileMap = new EditTileMap(15, 13);
    tileMap->UpdateWorld();

    player = new Player();
    player->SetGlobalPosition(CENTER);

    quad = new Quad(L"ResourcesCA/Textures/Character/Bazzi/Run.png", false);
    quad->SetLocalPosition(CENTER);
    quad->Update();
}

MapEditScene::~MapEditScene()
{
    delete tileMap;
    delete player;
}

void MapEditScene::Update()
{
    tileMap->Update();
    tileMap->UpdateWorld();
    
    player->Update();
    player->UpdateWorld();
}

void MapEditScene::Render()
{
    tileMap->Render();
    player->Render();
   // quad->Render();
}

void MapEditScene::PostRender()
{
    tileMap->RenderSampleButtons();
}
