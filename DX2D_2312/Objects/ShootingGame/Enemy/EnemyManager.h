#pragma once

class EnemyManager : public Singleton<EnemyManager>, public PoolingManager<Enemy>
{
private:
	const float SPAWN_INTERVAL = 1.0f;

private:
	friend class Singleton;

	EnemyManager();
	
public:
	void Update();

	void SetTarget(Transform* transform);		

	GameObject* GetClosestEnemy(const Vector2& pos);

private:
	Vector2 GetRandomPos();

private:
	float playTime = 0.0f;

	vector<Enemy*> enemies;
};