#pragma once

class BasicTile : public Tile
{
public:
	BasicTile(Data data);
	~BasicTile();

	void Render() override;
};
