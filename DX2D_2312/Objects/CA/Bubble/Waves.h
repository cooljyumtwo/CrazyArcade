#pragma once

class WaveManager : public GameObject
{
private:
	const string PATH = "ResourcesCA/Textures/Bubble/";

	const float MAX_PLAY_TIME = 2.0f;
	const int MAX_POWER;

	enum State
	{
		L, R, U, D
	};

public:
	WaveManager();
	~WaveManager();

	void Update();
	void Render();

	void CreatActions();

	void Spawn(const Vector2& pos, int power);

	void SetAction(int state);

private:
	State curState = L;

	int power;

	map<State, Wave*> waves;

	float playTime = 0.0f;
};