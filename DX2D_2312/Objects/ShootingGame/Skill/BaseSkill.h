#pragma once

class BaseSkill : public Skill
{
private:
	const float EPSILON = 5.0f;

public:
	BaseSkill(Transform* owner);
	~BaseSkill();

	void Update() override;
	void Render() override;

private:
	void Fire();
	void Rotate();

private:
	float time = 0.0f;
	float rotSpeed = 10.0f;

	GameObject* target = nullptr;
};