#pragma once

class Wave : public GameObject
{
private:
	const string PATH = "ResourcesCA/Textures/Bubble/";
	const int MAX_POWER = 5.0f;

public:
	enum State
	{
		START, END
	};

	enum Direction
	{
		R, L, U, D
	};

public:
	Wave();
	~Wave();

	void Update();
	void Render();
	float GetDepth() override;

	void CreateActions();

	void Spawn(const Vector2& pos, Direction direction = R ,State state = START);

	Action* GetAction() { return actions[curState]; }

	void SetAction(int state);
	void SetPosTileIdx(Vector2 posTileIdx) { this->posTileIdx = posTileIdx; }

private:
	int power;
	
	Vector2 posTileIdx;

	State curState = START;
	Direction direction = R;

	map<State, Action*> actions;
};