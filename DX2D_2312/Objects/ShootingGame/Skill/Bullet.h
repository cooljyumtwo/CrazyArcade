#pragma once

class Bullet : public Quad
{
public:
	Bullet(wstring textureFile, Vector2 startUV = Vector2(),
		Vector2 endUV = Vector2(1, 1));
	~Bullet();

	virtual void Update();
	void Render();

	void Fire(const Vector2& pos, const Vector2& direction, float power, float speed);	
	void Fire(const Vector2& pos, const Vector2& direction, SkillData data);

	Collider* GetCollider() { return collider; }
	SkillData GetData() { return data; }

	void SetData(SkillData data) { this->data = data; }

protected:
	SkillData data;
	
	Vector2 velocity;

	Collider* collider;
};