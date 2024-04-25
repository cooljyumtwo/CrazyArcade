#include "Framework.h"

MonsterDie::MonsterDie(Transform* target ,int key)
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Die.png", 3, 1, false, 1.0f);
}

void MonsterDie::End()
{
	target->SetActive(false);
}
