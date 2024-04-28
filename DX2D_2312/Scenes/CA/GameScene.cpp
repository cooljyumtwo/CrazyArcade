#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
    CAM->SetFix(false);

    player = new Player();
    player->SetGlobalPosition(CENTER);

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

    TileManager::Get()->Update();
    BubbleManager::Get()->Update();
    ItemManager::Get()->Update();
    EffectManager::Get()->Update();
    MonsterManager::Get()->Update();
}

void GameScene::Render()
{
    RenderManager::Get()->Render("BGTile");
    RenderManager::Get()->Render("GameObject");
    RenderManager::Get()->Render("BGTileTxt");

    EffectManager::Get()->Render();
    MonsterManager::Get()->Render();
}

void GameScene::PostRender()
{
}

void GameScene::Start()
{
    TileManager::Get()->LoadMapData();
    TileManager::Get()->LoadMapSize();
    MonsterManager::Get()->LoadMonster();
}

void GameScene::End()
{
    TileManager::Get()->ClearObjTile();
    MonsterManager::Get()->ClearMonster();
}