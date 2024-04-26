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
		if (!GameManager::isDraw) return;
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

void RenderManager::Remove(string key, GameObject* gameObj)
{
	auto& gameObjList = gameObjects[key];

	for (auto it = gameObjList.begin(); it != gameObjList.end(); ++it)
	{
		if (*it == gameObj)
		{
			gameObjList.erase(it);
			return;
		}
	}
}
