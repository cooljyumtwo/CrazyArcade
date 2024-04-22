#include "Framework.h"

void EffectManager::Render()
{
	for (const auto& pair : totalObject) {
		const vector<GameObject*>& gameObjects = pair.second;
		for (GameObject* object : gameObjects) {
			object->Render();
		}
	}
}

void EffectManager::Update()
{
	for (const auto& pair : totalObject) {
		const vector<GameObject*>& gameObjects = pair.second;
		for (GameObject* object : gameObjects) {
			object->Update();
		}
	}
}

void EffectManager::Add(string key, UINT poolSize, wstring textureFile, Vector2 maxFrame, float speed, bool isAdditive)
{
	vector<GameObject*> objects(poolSize);

	for (GameObject*& object : objects)
		object = new Effect(textureFile, maxFrame, speed, isAdditive);

	totalObject[key] = objects;
}

void EffectManager::Play(string key, const Vector2& pos)
{
	Effect* effect = Pop(key);
	effect->Play(pos);
}
