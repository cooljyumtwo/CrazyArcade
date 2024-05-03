#pragma once

class StageManager : public Singleton<StageManager>
{
public:
	const int PLAYER_SPAWN_HP = 3;
private:
	friend class Singleton;

	StageManager();
	~StageManager() = default;

public:

	void SetStageData();
	void SetPlayer(Character* playerCharacter);
	void LoadStage();
	void NextStage();
	void SpawnPlayer(bool isSpawn = false);

	void Start();
	void Clear();
	void Gameover();

	void SetGameUIState(GameUI::State state);

	void End();
	
public:
	StageData stageData;
	int countStage;
	int maxStage;
	vector<string> stageMapNames;

	GameUI* gameUI;

	Character* playerCharacter;
	
	int userHp = PLAYER_SPAWN_HP;
};
