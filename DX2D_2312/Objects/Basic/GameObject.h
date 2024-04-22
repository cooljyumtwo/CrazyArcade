#pragma once

class GameObject : public Transform
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Render() = 0;

	void SetRender();

	Material* GetMaterial() { return material; }

	virtual float GetDepth();

	static bool Compare(GameObject* obj1, GameObject* obj2);

protected:
	Material* material;
	MatrixBuffer* worldBuffer;
};