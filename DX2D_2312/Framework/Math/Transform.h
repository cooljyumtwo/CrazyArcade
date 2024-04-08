#pragma once

class Transform
{
public:
	Transform();
	~Transform() = default;

	virtual void UpdateWorld();
	void RenderUI();

	void Save();
	void Load();

	bool IsActive();
	bool IsActiveSelf() { return isActive; }

	void Translate(Vector2 direction) { localPosition += direction; }
	void Rotate(float value) { localRotation.z += value; }

	Vector2 GetRight() { return right.Normalized(); }
	Vector2 GetLeft() { return right.Normalized() * -1.0f; }
	Vector2 GetUp() { return up.Normalized(); }
	Vector2 GetDown() { return up.Normalized() * -1.0f; }

	Vector2 GetGlobalPosition() { return globalPosition; }
	Vector2 GetGlobalScale() { return globalScale; }

	string GetTag() { return tag; }	

	Transform* GetParent() { return parent; }

	Vector2 GetLocalPosition() { return localPosition; }
	Float3 GetLocalRotation() { return localRotation; }
	Vector2 GetLocalScale() { return localScale; }

	void SetLocalPosition(Vector2 pos) { localPosition = pos; }
	void SetLocalPosition(float x, float y) { localPosition = { x, y }; }
	void SetLocalRotation(float x, float y, float z) { localRotation = { x, y, z }; }
	void SetLocalScale(Vector2 scale) { localScale = scale; }
	void SetLocalScale(float x, float y) { localScale = { x, y }; }
	void SetPivot(Vector2 pivot) { this->pivot = pivot; }

	void SetGlobalPosition(Vector2 pos);

	void SetParent(Transform* transform) { parent = transform; }
	void SetActive(bool isActive) { this->isActive = isActive; }

	void SetTag(string tag) { this->tag = tag; }

protected:
	string tag;	

	Vector2 localPosition;
	Float3 localRotation;
	Vector2 localScale = { 1, 1 };	
	Vector2 pivot;

	Matrix world;	
	
private:
	bool isActive = true;

	Transform* parent = nullptr;

	Matrix S, R, T;
	Matrix P, IP;
	XMFLOAT4X4 matWorld;

	Vector2 globalPosition;
	Vector2 globalScale = { 1, 1 };
	Vector2 right, up;
};