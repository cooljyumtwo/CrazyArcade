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

	float GetDepth() override;
	Collider* GetCollider() { return collider; }

	void CreatActions();
	void SetAction(int state);

	void Spawn(const Vector2& pos, int power, Character* target);

protected:
	int power;

	float playTime = 0.0f;

	Vector2 velocity;
	Vector2 posTileIdx;

	RectCollider* collider;

	Character* target;

	State curState = STAND;

	map<State, Action*> actions;
};