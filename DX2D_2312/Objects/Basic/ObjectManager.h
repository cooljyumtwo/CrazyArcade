#pragma once

class ObjectManager : public Singleton<ObjectManager>
{
private:
	friend class Singleton;

	ObjectManager();
	~ObjectManager();

public:
	void Update();
	void Render();	

	void Add(GameObject* object);
	void Delete(GameObject* object);

private:
	vector<GameObject*> objects;	
	unordered_set<GameObject*> findObjects;
};