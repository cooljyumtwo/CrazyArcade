#pragma once

class StageManager : public Singleton<StageManager>
{
private:
	friend class Singleton;

	StageManager();
	~StageManager() = default;

public:
	//StageData GetCurStageData() { return stageData; }

	void SetStageData();
	void LoadStage();
	void NextStage();

	void Ready();
	void Clear();
	void Gameover();
	void End();
	
public:
	StageData stageData;
	int countStage;
	int maxStage;
	vector<string> stageMapNames;

	GameUI* gameUI;
	
};
