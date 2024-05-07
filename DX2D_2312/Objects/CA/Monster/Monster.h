#pragma once

class Monster : public Character
{
	
public:
	Monster(int key, float speed, bool isBubble = false, int hp = 1, bool isBoss = false);
	~Monster();

	void Update() override;
	void CreateActions() override;

	virtual void CheckTileHit();
	bool CheckHitCollider(Collider* collider);
	void Hit(Collider* collider);
	void Die();

	void PlusHp() { hp++; }

	void Spawn(const Vector2& pos);

	void RemoveHitColliders();

	void Collision(Character* character);
	bool Collision(Tile* tile);

	Character* GetPlayer() {return player;}

	bool GetIsBoss() { return isBoss; }

protected:
	int key;
	int hp;
	float speed;
	bool isBubble;
	bool isBoss;

	vector<Collider*> hitColliders;

	Character* player;

public:
	State curType = MOVE;
};