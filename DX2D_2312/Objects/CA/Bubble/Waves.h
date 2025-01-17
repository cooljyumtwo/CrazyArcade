#pragma once

class Waves : public GameObject
{
private:
	const string PATH = "ResourcesCA/Textures/Bubble/";

	const int MAX_POWER = 5;

	enum Direction
	{
		R, L, U, D
	};

public:
	Waves();
	~Waves();

	void Update();
	void Render();

	void CreateWaves();
	void CreateDirectionWaves(Direction direction);

	void ClearWaves();

	void Spawn(const Vector2& pos, int power);

private:
	int power;

	map<Direction, vector<Wave*>> waves;
};