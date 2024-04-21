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

	void CreateActions();

	void Spawn(const Vector2& pos, Direction direction = R ,State state = START);

	void SetAction(int state);
	void SetPosTileIdx(Vector2 posTileIdx) { this->posTileIdx = posTileIdx; }

	Action* GetAction() { return actions[curState]; }

	void End();

private:
	State curState = START;
	Direction direction = R;

	int power;

	Vector2 velocity;

	RectCollider* collider;

	map<State, Action*> actions;


	Vector2 posTileIdx;
};