#pragma once

class Wave : public GameObject
{
private:
	const string PATH = "ResourcesCA/Textures/Bubble/";
	const float MAX_PLAY_TIME = 2.0f;
	const int MAX_POWER = 5.0f;

	enum State
	{
		L, R, U, D
	};

public:
	Wave();
	~Wave();

	void Update();
	void Render();

	void CreatActions();

	void Spawn(const Vector2& pos, int power, State state = L);

	void SetAction(int state);

private:
	State curState = L;

	int power;

	Vector2 velocity;

	RectCollider* collider;

	map<State, Action*> actions;
	

	float playTime = 0.0f;
};