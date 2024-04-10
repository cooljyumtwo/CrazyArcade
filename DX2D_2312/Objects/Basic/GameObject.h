#pragma once

class GameObject : public Transform
{
public:
	GameObject(bool isAdd = false);
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Render() = 0;

	void SetRender();

	int GetDepth() { return depth; }
	Material* GetMaterial() { return material; }

	void SetDepth(int depth) { this->depth = depth; }

	static bool Compare(GameObject* obj1, GameObject* obj2);

protected:
	int depth = 0;

	Material* material;
	MatrixBuffer* worldBuffer;
};