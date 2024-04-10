#pragma once

class Quad : public GameObject
{
public:
	Quad(Vector2 size = { 100, 100 }, bool isAdd = true);
	Quad(wstring textureFile, bool isAdd = true, Vector2 startUV = Vector2(), 
		Vector2 endUV = Vector2(1, 1), Vector2 pos = Vector2());	
	~Quad();

	virtual void Update() override;
	virtual void Render() override;

	void SetRender();

	void SetTexture(wstring textureFile);

	Vector2 GetSize() { return size * GetGlobalScale(); }

private:
	void MakeMesh(Vector2 startUV = Vector2(), Vector2 endUV = Vector2(1, 1), Vector2 pos = Vector2());

protected:
	Mesh<VertexUV>* mesh;	

	Vector2 size;	
};
