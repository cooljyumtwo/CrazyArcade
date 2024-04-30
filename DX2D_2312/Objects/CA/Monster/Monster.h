#pragma once

class Monster : public Character
{
	
public:
	Monster(int key, float speed, bool isBubble = false, int hp = 1);
	~Monster();

	void Update() override;
	void CreateActions() override;

	void CheckHit();
	void Hit(Collider* collider);
	void Die();

	void PlusHp() { hp++; }

	void Spawn(const Vector2& pos);

	void RemoveHitColliders();

	void Collision(Character* character);
	Character* GetPlayer() {return player;}


protected:
	int key;
	int hp;
	float speed;
	bool isBubble;

	vector<Collider*> hitColliders;

	Character* player;
};