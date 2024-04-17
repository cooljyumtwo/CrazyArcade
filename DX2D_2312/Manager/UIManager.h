#pragma once

class UIManager : public Singleton<UIManager>
{
private:
	friend class Singleton;

	UIManager() = default;
	~UIManager();

public:
	void Update();

	void PreRender();
	void Render();
	void PostRender();

	void Add(string key, UI* scene);

	void ChangeUI(string key);

private:
	map<string, UI*> UIs;

	UI* curUI = nullptr;
};