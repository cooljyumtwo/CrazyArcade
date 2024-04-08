#pragma once

class Enemy : public Quad
{
public:
	Enemy(EnemyData data);
	~Enemy();

	void Update() override;
	void Render() override;

	void Spawn();

	CircleCollider* GetCollider() { return collider; }

	void SetTarget(Transform* transform) { target = transform; }

protected:
	virtual void Move();

private:
	void Collision();
	void RemoveHitCollider();

	void Damage(string key);
	void Dead();

private:	
	CircleCollider* collider;
	Transform* target;

	ProgressBar* hpBar;
	Vector2 hpBarOffset;

	int hp;

	vector<Collider*> hitColliders;

protected:
	EnemyData data;
	Vector2 direction;
};