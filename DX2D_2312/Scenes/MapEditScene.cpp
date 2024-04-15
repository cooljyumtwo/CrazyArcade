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

    TileObjectManager::Get();
    BubbleManager::Get();

    t = new TileObject();
   // t->Spawn(CENTER,  L"ResourcesCA/Textures/Tiles/Obstacle/Obstacle (1).png");

    //tileMap->Load();
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

    t->Update();
    TileObjectManager::Get()->Update();
    BubbleManager::Get()->Update();
}

void MapEditScene::Render()
{
    tileMap->PreRender();
    player->Render();
    tileMap->Render();
    TileObjectManager::Get()->Render();
    BubbleManager::Get()->Render();
   // quad->Render();
    t->Render();
    tileMap->PostRender();
}

void MapEditScene::PostRender()
{
    tileMap->RenderSampleButtons();
}
