#pragma once

class BubbleManager : public Singleton<BubbleManager>, public PoolingManager<GameObject>
{
private:
	friend class Singleton;

	const UINT POOL_SIZE = 10;

	BubbleManager();
	~BubbleManager();

public:
	void Render();
	void Update();

	void Spawn(const Vector2& pos, int power, Character* target = nullptr);
	void SpawnWaves(const Vector2& pos, int power);

	Bubble* PushPlayer(Character* player, bool isPlayerMaxSpeed = false);

	void CollisionBoss(Boss* boss);

public:
	vector<GameObject*> bubbles;
	vector<Wave*> waves;
};