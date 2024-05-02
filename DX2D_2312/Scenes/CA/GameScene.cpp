#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
    Audio::Get()->Add("BtnClick", AUDIO_PATH + "BtnClick.mp3", false, false);
    Audio::Get()->Add("BtnHover", AUDIO_PATH + "BtnHover.wav", false, false);

    Audio::Get()->Add("BubbleAdd", AUDIO_PATH + "BubbleAdd.wav", false, false);

    Audio::Get()->Add("MonsterDie", AUDIO_PATH + "MonsterDie.wav", false, false);

    Audio::Get()->Add("BossDie", AUDIO_PATH + "BossDie.wav", false, false);
    Audio::Get()->Add("BossHit", AUDIO_PATH + "BossHit.wav", false, false);
    Audio::Get()->Add("BossMove", AUDIO_PATH + "BossMove.wav", false, false);
    Audio::Get()->Add("BossMonsterSpawn", AUDIO_PATH + "BossMonsterSpawn.wav", false, false);
    Audio::Get()->Add("BossBubble", AUDIO_PATH + "BossBubble.wav", false, false);

    Audio::Get()->Add("GameStart", AUDIO_PATH + "GameStart.wav", false, false);
    Audio::Get()->Add("Clear", AUDIO_PATH + "Clear.wav", false, false);
    Audio::Get()->Add("Lose", AUDIO_PATH + "Lose.wav", false, false);
    Audio::Get()->Add("NextLevelReady", AUDIO_PATH + "NextLevelReady.wav", false, false);

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
    RenderManager::Get()->Render("BGTile");
    RenderManager::Get()->Render("GameObject");
    RenderManager::Get()->Render("BGTileTxt");

    EffectManager::Get()->Render();
    MonsterManager::Get()->Render();
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
}

void GameScene::End()
{
    TileManager::Get()->ClearObjTile();
    MonsterManager::Get()->ClearMonster();
}