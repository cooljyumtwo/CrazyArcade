#pragma once

class ObstacleTile : public Tile
{
private:
	const float OFFSET_DISTANCE = 0.1f;
public:
	ObstacleTile(wstring textureFile, Vector2 pos, bool isPop = false, bool isPush = false);
	~ObstacleTile();

	void Update() override;
	bool GetIsPop() { return isPop; }
	void SetIsPop(bool isPop) { this->isPop = isPop; }

	bool GetIsPush() { return isPush; }
	void SetIsPush(bool isPush) { this->isPush = isPush; }
	
	void SetTarget(GameObject* target);

	void Move();
	void Deactivate();

private:
	bool isPop = false;
	bool isPush = false;

	Vector2 velocity;
	GameObject* target;

	bool isMove = false;

	float speed = 100.0f;
};