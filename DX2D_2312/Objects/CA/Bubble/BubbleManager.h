#pragma once

class BubbleManager : public Singleton<BubbleManager>, public PoolingManager<Bubble>
{
private:
	friend class Singleton;

	const UINT POOL_SIZE = 50;

	BubbleManager();
	~BubbleManager();

public:
	void Render();
	void Update();

public:
	Bubble* Collision(string key, Collider* collider);

public:
	void Spawn(const Vector2& pos, int power);

	vector<Bubble*> bubbles;
};