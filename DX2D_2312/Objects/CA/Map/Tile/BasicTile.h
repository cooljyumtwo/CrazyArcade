#pragma once

class BasicTile : public Tile
{
public:
	BasicTile(wstring textureFile, Vector2 pos);
	~BasicTile();

	void SetObstacleTile(Tile* tile) { this->obstacleTile = tile; };
	Tile* GetObstacleTile() { return obstacleTile; }

private:
	Tile* obstacleTile = nullptr;
};
