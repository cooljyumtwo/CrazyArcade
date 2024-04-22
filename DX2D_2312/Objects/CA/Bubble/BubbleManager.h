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

	Bubble* Collision(string key, Collider* collider);

	void Spawn(const Vector2& pos, int power);
	void SpawnWaves(const Vector2& pos, int power);

	void PushPlayer(Character* player);

public:
	vector<Bubble*> bubbles;
	vector<Wave*> waves;
};