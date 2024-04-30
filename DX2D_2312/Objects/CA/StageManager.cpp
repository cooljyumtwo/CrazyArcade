#include "Framework.h"

StageManager::StageManager()
{
}

void StageManager::SetStageData()
{
	stageData = DataManager::Get()->GetStageData(WaitRoomUI::stageKey);
}

void StageManager::LoadStage()
{
	SetStageData();
	countStage = 0;

	if (stageData.stage1 != "")
	{
		maxStage++;
	}
	if (stageData.stage2 != "")
	{
		maxStage++;
	}
	if (stageData.stage3 != "")
	{
		maxStage++;
	}
	stageMapNames.resize(maxStage);

	stageMapNames[0] = stageData.stage1;
	stageMapNames[1] = stageData.stage2;
	stageMapNames[2] = stageData.stage3;

	NextStage();
}

void StageManager::NextStage()
{
	if (countStage > maxStage) return;

	TileManager::Get()->SetMap(stageMapNames[countStage]);
	TileManager::Get()->LoadMapData();
	TileManager::Get()->LoadMapSize();
	MonsterManager::Get()->LoadMonster();
	Ready();

	countStage++;
}

void StageManager::Ready()
{
	UI* curUI = UIManager::Get()->GetUI("Game");
	gameUI = (GameUI*)curUI;
	gameUI->SetGameTxt(GameUI::State::START);
}

void StageManager::Clear()
{
	UI* curUI = UIManager::Get()->GetUI("Game");
	gameUI = (GameUI*)curUI;
	gameUI->SetGameTxt(GameUI::State::CLEAR);
}

void StageManager::Gameover()
{
	UI* curUI = UIManager::Get()->GetUI("Game");
	gameUI = (GameUI*)curUI;
	gameUI->SetGameTxt(GameUI::State::GAMEOVER);
}

void StageManager::End()
{
}
