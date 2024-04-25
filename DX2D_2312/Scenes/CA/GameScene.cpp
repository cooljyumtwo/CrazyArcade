#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
    CAM->SetFix(false);

    player = new Player();
    player->SetGlobalPosition(CENTER);

    TileObjectManager::Get();
    BubbleManager::Get();
    ItemManager::Get();
    EffectManager::Get();
    DataManager::Get();
    MonsterManager::Get();

    RenderManager::Get()->Add("GameObject", player);
}

GameScene::~GameScene()
{
    delete player;
}

void GameScene::Update()
{
    player->Update();

    TileObjectManager::Get()->Update();
    TileManager::Get()->Update();
    BubbleManager::Get()->Update();
    ItemManager::Get()->Update();
    EffectManager::Get()->Update();
    MonsterManager::Get()->Update();
}

void GameScene::Render()
{
    RenderManager::Get()->Render();
    TileObjectManager::Get()->Render();
    TileManager::Get()->Render();
    ItemManager::Get()->Render();
    EffectManager::Get()->Render();
    MonsterManager::Get()->Render();
}

void GameScene::PostRender()
{
}

void GameScene::Start()
{
    TileManager::Get()->LoadGameMap();
}
