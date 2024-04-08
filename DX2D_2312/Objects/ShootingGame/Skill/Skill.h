#pragma once

class Skill : public GameObject
{
public:
	Skill(int key, Transform* owner);
	virtual ~Skill();

	virtual void LevelUp();

	void SetData(int key);

	SkillData GetData() { return data; }

protected:
	SkillData data;

	Transform* owner;
};