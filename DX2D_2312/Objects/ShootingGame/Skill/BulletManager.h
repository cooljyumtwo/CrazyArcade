#pragma once

class BulletManager : public Singleton<BulletManager>, public PoolingManager<Bullet>
{
private:
	friend class Singleton;

	const UINT POOL_SIZE = 50;	

	BulletManager();
	~BulletManager();

public:
	Bullet* Collision(string key, Collider* collider);

public:
	void Fire(const Vector2& pos, const Vector2& direction, float power, float speed);
	void Fire(const Vector2& pos, const Vector2& direction, SkillData data);
	void Fire(string key, const Vector2& pos, const Vector2& direction, float power, float speed);
};