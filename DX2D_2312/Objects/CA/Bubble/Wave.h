#pragma once

class Wave : public GameObject
{
private:
	const string PATH = "ResourcesCA/Textures/Bubble/";
	const int MAX_POWER = 5.0f;

	enum State
	{
		START, END
	};

public:
	Wave();
	~Wave();

	void Update();
	void Render();

	void CreatActions();

	void Spawn(const Vector2& pos, int power, State state = START);

	void SetAction(int state);

private:
	State curState = START;

	int power;

	Vector2 velocity;

	RectCollider* collider;

	map<State, Action*> actions;
	
	Action* action;
};