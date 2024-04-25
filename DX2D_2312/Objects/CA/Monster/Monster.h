#pragma once

class Monster : public Character
{
private:
	
public:
	Monster(int key, float speed, bool isBubble = false);
	~Monster();

	void Update() override;
	void CreateActions() override;

	void Die();

	void Spawn(const Vector2& pos);

private:
	int key;
	float speed;
	bool isBubble;

};