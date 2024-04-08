#pragma once

class Plane : public Quad
{
public:
	Plane();
	~Plane();

	void Update();
	void Render();
	void PostRender();
	
	CircleCollider* GetCollider() { return collider; }
	Quad* GetCursor() { return cursor; }

private:
	void Collision();
	void AddExp(int value);

	void SkillLevelUp(int index);

	void SaveData();
	void LoadData();

private:
	float speed = 200.0f;

	CircleCollider* collider;
	Quad* cursor;

	vector<Skill*> skills;

	int hp = 100;
	int exp = 0;
	int level = 1;	

	LevelData levelData;
};