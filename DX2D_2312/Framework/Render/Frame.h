#pragma once

class Frame
{
public:
	Frame(wstring textureFile, Vector2 startUV = Vector2(),
		Vector2 endUV = Vector2(1, 1), Vector2 pos = Vector2());
	Frame(wstring textureFile, float x, float y, float width, float height);
	~Frame();

	void Render();

	Vector2 GetSize() { return size; }
	Material* GetMaterial() { return material; }

private:
	void MakeMesh(Vector2 startUV = Vector2(), Vector2 endUV = Vector2(1, 1), Vector2 pos = Vector2());

protected:
	Material* material;
	Mesh<VertexUV>* mesh;

	Vector2 size;
};