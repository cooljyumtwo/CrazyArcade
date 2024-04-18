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

	if (key == "BGTileTxt")
	{
		for (GameObject* gameObj : gameObjects[key])
		{
			Tile* tile = (Tile*)gameObj;
			Font::Get()->RenderText(to_string(tile->GetType()), gameObj->GetGlobalPosition());
		}
		return;
	}

	for (GameObject* gameObj : gameObjects[key])
	{
		if (!gameObj->IsActive()) continue;

		gameObj->Render();
	}
}

void RenderManager::Add(string key, GameObject* gameObj)
{
	gameObjects[key].push_back(gameObj);
}
