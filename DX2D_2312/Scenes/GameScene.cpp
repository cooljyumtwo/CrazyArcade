#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
    CAM->SetFix(false);

   // tileMap = new EditTileMap(15, 13);
   // tileMap->UpdateWorld();

    player = new Player();
    player->SetGlobalPosition(CENTER);

    quad = new Quad(L"ResourcesCA/Textures/Character/Bazzi/Run.png", false);
    quad->SetLocalPosition(CENTER);
    quad->Update();

    TileObjectManager::Get();
    TileManager::Get();
    BubbleManager::Get();

    t = new TileObject();
    // t->Spawn(CENTER,  L"ResourcesCA/Textures/Tiles/Obstacle/Obstacle (1).png");

     //tileMap->Load();
}

GameScene::~GameScene()
{
    //delete tileMap;
    delete player;
}

void GameScene::Update()
{
    //tileMap->Update();
    //tileMap->UpdateWorld();

    player->Update();
    player->UpdateWorld();

    t->Update();
    TileObjectManager::Get()->Update();
    TileManager::Get()->Update();
    BubbleManager::Get()->Update();
   
}

void GameScene::Render()
{
    //tileMap->PreRender();
    player->Render();
    //tileMap->Render();
    TileObjectManager::Get()->Render();
    TileManager::Get()->Render();
    BubbleManager::Get()->Render();
    // quad->Render();
    t->Render();
   // tileMap->PostRender();
}

void GameScene::PostRender()
{
    //tileMap->RenderSampleButtons();
}
