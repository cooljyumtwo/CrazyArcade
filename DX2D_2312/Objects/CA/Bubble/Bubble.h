#pragma once

class Bubble : public GameObject
{
private:
	const string PATH = "ResourcesCA/Textures/Bubble/";

	enum State
	{
		STAND, POP
	};

public:
	Bubble();
	~Bubble();

	virtual void Update();
	void Render();

	void Spawn(const Vector2& pos, int power);

	Collider* GetCollider() { return collider; }


protected:
	State state;

	int power;

	Vector2 velocity;

	Collider* collider;

	map<State, Action*> actions;
};