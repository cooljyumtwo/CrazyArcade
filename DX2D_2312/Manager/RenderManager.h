#pragma once

class RenderManager : public Singleton<RenderManager>
{
private:
	friend class Singleton;

	RenderManager() = default;
	~RenderManager();

public:
	void Update();

	void Render();
	void Render(string key);

	void Add(string key, GameObject* gameObj);

private:
	map<string, vector<GameObject*>> gameObjects;
};