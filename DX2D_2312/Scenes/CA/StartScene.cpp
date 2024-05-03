#include "Framework.h"
#include "StartScene.h"

StartScene::StartScene()
{
	CreateAudio();
}

StartScene::~StartScene()
{
}

void StartScene::Update()
{
}

void StartScene::Render()
{
}

void StartScene::PostRender()
{
}

void StartScene::Start()
{
    GameManager::isGUI = false;

    if (!Audio::Get()->IsPlaySound("StartBgm"))
    {
        Audio::Get()->Play("StartBgm", 0.5f);
    }
}

void StartScene::End()
{
    Audio::Get()->Stop("StartBgm");
}

void StartScene::CreateAudio()
{
    Audio::Get()->Add("BtnClick", AUDIO_PATH + "BtnClick.mp3", false, false);
    Audio::Get()->Add("BtnHover", AUDIO_PATH + "BtnHover.wav", false, false);

    Audio::Get()->Add("BubbleAdd", AUDIO_PATH + "BubbleAdd.wav", false, false);
    Audio::Get()->Add("BubblePop", AUDIO_PATH + "BubblePop.wav", false, false);

    Audio::Get()->Add("CharacterDie", AUDIO_PATH + "CharacterDie.wav", false, false);
    Audio::Get()->Add("CharacterBubble", AUDIO_PATH + "CharacterBubble.wav", false, false);
    Audio::Get()->Add("CharacterLive", AUDIO_PATH + "CharacterLive.wav", false, false);
    Audio::Get()->Add("PlayerSpawn", AUDIO_PATH + "PlayerSpawn.wav", false, false);

    Audio::Get()->Add("ItemAdd", AUDIO_PATH + "ItemAdd.mp3", false, false);

    Audio::Get()->Add("MonsterDie", AUDIO_PATH + "MonsterDie.wav", false, false);
    Audio::Get()->Add("MonsterChangeIdle", AUDIO_PATH + "MonsterChangeIdle.wav", false, false);

    Audio::Get()->Add("BossDie", AUDIO_PATH + "BossDie.wav", false, false);
    Audio::Get()->Add("BossHit", AUDIO_PATH + "BossHit.wav", false, false);
    Audio::Get()->Add("BossMove", AUDIO_PATH + "BossMove.wav", false, false);
    Audio::Get()->Add("BossMonsterSpawn", AUDIO_PATH + "BossMonsterSpawn.wav", false, false);
    Audio::Get()->Add("BossBubble", AUDIO_PATH + "BossBubble.wav", false, false);

    Audio::Get()->Add("GameStart", AUDIO_PATH + "GameStart.wav", false, false);
    Audio::Get()->Add("Clear", AUDIO_PATH + "Clear.wav", false, false);
    Audio::Get()->Add("Lose", AUDIO_PATH + "Lose.wav", false, false);
    Audio::Get()->Add("NextLevelReady", AUDIO_PATH + "NextLevelReady.wav", false, false);

    Audio::Get()->Add("GameBgm", AUDIO_PATH + "GameBgm.wav", true, true);
    Audio::Get()->Add("GameBossBgm", AUDIO_PATH + "GameBossBgm.wav", true, true);
    Audio::Get()->Add("WaitRoomBgm", AUDIO_PATH + "WaitRoomBgm.wav", true, true);
    Audio::Get()->Add("StartBgm", AUDIO_PATH + "StartBgm.wav", true, true);
    Audio::Get()->Add("MapEditBgm", AUDIO_PATH + "MapEditBgm.wav", true, true);
}
