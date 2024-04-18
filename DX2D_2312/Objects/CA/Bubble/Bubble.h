#pragma once

class Bubble : public GameObject
{
private:
	const string PATH = "ResourcesCA/Textures/Bubble/";
	const float MAX_PLAY_TIME = 2.0f;

	enum State
	{
		STAND, POP
	};

public:
	Bubble();
	~Bubble();

	void Update();
	void Render();

	void CreatActions();

	void Spawn(const Vector2& pos, int power);

	Collider* GetCollider() { return collider; }

	float GetDepth() override;

	void SetAction(int state);


protected:
	State curState = STAND;

	int power;

	Vector2 velocity;

	RectCollider* collider;

	map<State, Action*> actions;

	float playTime = 0.0f;

	Wave* wave;
};