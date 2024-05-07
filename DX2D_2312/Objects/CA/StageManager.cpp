#include "Framework.h"

StageManager::StageManager()
{
}

void StageManager::SetStageData()
{
	stageData = DataManager::Get()->GetStageData(WaitRoomUI::stageKey);
	userHp = PLAYER_SPAWN_HP;
	countStage = 0;
	maxStage = 0;
	score = 0;

	UI* curUI = UIManager::Get()->GetUI("Game");
	GameUI* gameUI = (GameUI*)curUI;

	gameUI->SetStateFont(0, userHp);
}

void StageManager::SetPlayer(Character* playerCharacter)
{
	this->playerCharacter = playerCharacter; 
}

void StageManager::LoadStage()
{
	SetStageData();

	if (stageData.stage1 != "")
		maxStage++;

	if (stageData.stage2 != "")
		maxStage++;

	if (stageData.stage3 != "")
		maxStage++;

	stageMapNames.resize(maxStage);

	stageMapNames[0] = stageData.stage1;
	stageMapNames[1] = stageData.stage2;
	stageMapNames[2] = stageData.stage3;

	NextStage();
}

void StageManager::NextStage()
{
	if (countStage >= maxStage)
	{
		SCENE->ChangeScene("WaitRoom");
		return;
	}
	if (countStage == maxStage - 1)
	{
		Audio::Get()->Stop("GameBgm");

		if (!Audio::Get()->IsPlaySound("GameBossBgm"))
		{
			Audio::Get()->Play("GameBossBgm", 0.5f);
		}
	}


	if (countStage <= 0)
	{
		if (!Audio::Get()->IsPlaySound("GameStart"))
			Audio::Get()->Play("GameStart");
	}
	else 
	{
		if (!Audio::Get()->IsPlaySound("NextLevelReady"))
			Audio::Get()->Play("NextLevelReady");
	}
		
	TileManager::Get()->SetMap(stageMapNames[countStage]);
	TileManager::Get()->LoadMapData();
	TileManager::Get()->LoadMapSize();

	MonsterManager::Get()->LoadMonster();

	ItemManager::Get()->ClearItems();

	SpawnPlayer(true);

	Start();

	countStage++;
}

void StageManager::SpawnPlayer(bool isSpawn)
{
	Player* player = (Player*)playerCharacter;
	player->LoadPos(isSpawn);

	playerCharacter->SetInit();
}

void StageManager::SetGameUIState(GameUI::State state)
{
	UI* curUI = UIManager::Get()->GetUI("Game");
	gameUI = (GameUI*)curUI;
	gameUI->SetGameTxt(state);
}

void StageManager::Start()
{
	SetGameUIState(GameUI::State::START);
}

void StageManager::Clear()
{
	if (!Audio::Get()->IsPlaySound("Clear"))
		Audio::Get()->Play("Clear");

	SetGameUIState(GameUI::State::CLEAR);
}

void StageManager::Gameover()
{
	if (userHp > 0)
	{	
		if (!Audio::Get()->IsPlaySound("PlayerSpawn"))
		{
			Audio::Get()->Play("PlayerSpawn");
		}
		SpawnPlayer();
	}
	else
	{
		if (!Audio::Get()->IsPlaySound("Lose"))
			Audio::Get()->Play("Lose");

		SetGameUIState(GameUI::State::GAMEOVER);
	}

	userHp--;

	UI* curUI = UIManager::Get()->GetUI("Game");
	GameUI* gameUI = (GameUI*)curUI;
	gameUI->SetStateFont(0, userHp);
}

void StageManager::End()
{
	SCENE->ChangeScene("WaitRoom");
}
