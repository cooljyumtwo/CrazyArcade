#include "Framework.h"

UIManager::~UIManager()
{
	for (pair<string, UI*> ui : UIs)
		delete ui.second;
}

void UIManager::Update()
{
	if (curUI == nullptr) return;

	curUI->Update();
}

void UIManager::PreRender()
{
	if (curUI == nullptr) return;

	curUI->PreRender();
}

void UIManager::Render()
{
	if (curUI == nullptr) return;

	curUI->Render();

	Environment::Get()->RenderUI();
	curUI->PostRender();
}

void UIManager::Add(string key, UI* scene)
{
	if (UIs.count(key) > 0)
	{
		assert(false);
	}

	//scenes.insert({ key, scene });
	//scenes.insert(make_pair(key, scene));
	//scenes.insert(pair<string, Scene*>(key, scene));
	UIs[key] = scene;
}

void UIManager::ChangeUI(string key)
{
	if (UIs.count(key) == 0)
	{
		assert(false);
	}

	if (UIs[key] == curUI)
		return;

	if (curUI != nullptr)
		curUI->End();

	curUI = UIs[key];
	curUI->Start();
}
