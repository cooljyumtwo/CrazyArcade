#include "Framework.h"

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
