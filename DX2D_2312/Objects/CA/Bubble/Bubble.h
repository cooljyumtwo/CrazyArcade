#pragma once

class Bubble : public GameObject
{
private:
	const string PATH = "ResourcesCA/Textures/Bubble/";
	const float MAX_PLAY_TIME = 2.0f;
	const float OFFSET_SIZE = 10.0f;

	enum State
	{
		STAND, POP
	};

public:
	enum PushDirection
	{
		NONE, R, L, U, D
	};

public:
	Bubble();
	~Bubble();

	void Update();
	void Render();

	void CreatActions();
	void SetAction(int state);

	void Spawn(const Vector2& pos, int power, Character* target);

	bool GetIsTarget() { return  isTarget; }
	void SetIsTarget(bool isTarget) {this->isTarget = isTarget;}

	void Pop();

	void SetPushDirection(PushDirection pushDirection) { this->pushDirection = pushDirection; }
	void SetIsPush(bool isPush) { this->isPush = isPush; }
	void Push();

protected:
	int power;

	float playTime = 0.0f;

	bool isTarget = false;
	bool isPush = false;

	Vector2 velocity;
	Vector2 posTileIdx;

	Character* target;

	State curState = STAND;

	map<State, Action*> actions;

	PushDirection pushDirection = NONE;
};