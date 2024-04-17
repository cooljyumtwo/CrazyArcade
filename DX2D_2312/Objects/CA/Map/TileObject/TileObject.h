#pragma once

class TileObject : public Quad
{
private:
public:
	TileObject();
	~TileObject();

	void Update();
	void Render();

	void Spawn(const Vector2& pos,const wstring textureFile);

	void AddAction(wstring file, int frameX, int frameY);

protected:
	Quad* img;
};