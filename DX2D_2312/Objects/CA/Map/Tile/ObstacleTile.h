#pragma once

class ObstacleTile : public Tile
{
public:
	ObstacleTile(wstring textureFile, Vector2 pos, bool isPop = false);
	~ObstacleTile();

	void SetIsPop(bool isPop) { this->isPop = isPop; }
	bool GetIsPop() { return isPop; }

	void End() { SetActive(false); EffectManager::Get()->Play("RemoveObstacle",GetGlobalPosition());}

private:
	bool isPop = false;
};