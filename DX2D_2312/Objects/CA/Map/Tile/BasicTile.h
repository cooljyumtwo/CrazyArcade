#pragma once

class BasicTile : public Tile
{
public:
	BasicTile(wstring textureFile, Vector2 pos);
	~BasicTile();

	Tile* GetObstacleTile() { return obstacleTile; }
	void SetObstacleTile(Tile* tile) { this->obstacleTile = tile; };

private:
	Tile* obstacleTile = nullptr;
};
