#pragma once

class BubbleManager : public Singleton<BubbleManager>, public PoolingManager<GameObject>
{
private:
	friend class Singleton;

	const UINT POOL_SIZE = 50;

	BubbleManager();
	~BubbleManager();

public:
	void Render();
	void Update();

	void Spawn(const Vector2& pos, int power, Character* target = nullptr);
	void SpawnWaves(const Vector2& pos, int power);

	void PushPlayer(Character* player);

public:
	vector<GameObject*> bubbles;
	vector<Wave*> waves;
};