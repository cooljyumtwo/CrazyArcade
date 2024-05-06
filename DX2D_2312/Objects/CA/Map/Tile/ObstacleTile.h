#pragma once

class ObstacleTile : public Tile
{
public:
	ObstacleTile(wstring textureFile, Vector2 pos, bool isPop = false, bool isPush = false);
	~ObstacleTile();

	void Update() override;
	bool GetIsPop() { return isPop; }
	void SetIsPop(bool isPop) { this->isPop = isPop; }

	bool GetIsPush() { return isPush; }
	void SetIsPush(bool isPush) { this->isPush = isPush; }
	
	void SetTargetPos(Vector2 targetPos) { this->targetPos= targetPos; }
	void Move();
	void Deactivate();

private:
	bool isPop = false;
	bool isPush = false;

	Vector2 velocity;
	Vector2 targetPos;
};