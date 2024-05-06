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
    StageManager::Get();

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
    RenderManager::Get()->Render("BGTileRander");
    RenderManager::Get()->Render("GameObject");
    RenderManager::Get()->Render("BGTileTxt");


    EffectManager::Get()->Render();
    MonsterManager::Get()->Render();
    TileManager::Get()->Render();
}

void GameScene::PostRender()
{
    RenderManager::Get()->Render("HpBar");
}

void GameScene::Start()
{
    StageManager::Get()->SetPlayer(player);
    StageManager::Get()->LoadStage();

    GameManager::isGUI = false;

    if (!Audio::Get()->IsPlaySound("GameBgm"))
    {
        Audio::Get()->Play("GameBgm", 0.5f);
    }
}

void GameScene::End()
{
    TileManager::Get()->ClearObjTile();
    MonsterManager::Get()->ClearMonster();

    Audio::Get()->Stop("GameBgm");
    Audio::Get()->Stop("GameBossBgm");
}