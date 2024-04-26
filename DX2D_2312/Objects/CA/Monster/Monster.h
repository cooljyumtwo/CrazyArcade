#pragma once

class Monster : public Character
{
private:
	
public:
	Monster(int key, float speed, bool isBubble = false, int hp = 1);
	~Monster();

	void Update() override;
	void CreateActions() override;

	void Hit();
	void Die();

	void Spawn(const Vector2& pos);

private:
	int key;
	int hp;
	float speed;
	bool isBubble;
};