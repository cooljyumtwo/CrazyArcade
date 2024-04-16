#include "Framework.h"

RenderManager::~RenderManager()
{
}

void RenderManager::Update()
{
}

void RenderManager::Render()
{

}

void RenderManager::Render(string key)
{
	sort(gameObjects[key].begin(), gameObjects[key].end(), &GameObject::Compare);

	for (GameObject* gameObj : gameObjects[key])
	{
		gameObj->Render();
	}
}

void RenderManager::Add(string key, GameObject* gameObj)
{
	gameObjects[key].push_back(gameObj);
}
