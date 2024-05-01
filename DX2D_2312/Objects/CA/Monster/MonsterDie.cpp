#include "Framework.h"

MonsterDie::MonsterDie(Transform* target ,int key, int max_frameX)
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Die.png", max_frameX, 1, false, 1.0f);
}

void MonsterDie::Start()
{
	Play();
}

void MonsterDie::End()
{
	target->SetActive(false);
}
