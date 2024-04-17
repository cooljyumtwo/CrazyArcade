#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
    CAM->SetFix(false);

    player = new Player();
    player->SetGlobalPosition(CENTER);

    quad = new Quad(L"ResourcesCA/Textures/Character/Bazzi/Run.png", false);
    quad->SetLocalPosition(CENTER);
    quad->Update();

    TileObjectManager::Get();
    BubbleManager::Get();
    RenderManager::Get()->Add("GameObject", player);
}

GameScene::~GameScene()
{
    delete player;
}

void GameScene::Update()
{

    player->Update();
    player->UpdateWorld();

    TileObjectManager::Get()->Update();
    TileManager::Get()->Update();
    BubbleManager::Get()->Update();
   
}

void GameScene::Render()
{
    TileManager::Get()->PreRender();
    //player->Render();
    RenderManager::Get()->Render();
    TileObjectManager::Get()->Render();
    TileManager::Get()->Render();
   // BubbleManager::Get()->Render();
    TileManager::Get()->PostRender();
}

void GameScene::PostRender()
{
}

void GameScene::Start()
{
    TileManager::Get()->LoadGameMap();
}
