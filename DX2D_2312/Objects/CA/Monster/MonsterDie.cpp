#include "Framework.h"

MonsterDie::MonsterDie(Transform* target ,int key, int max_frameX)
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Die.png", max_frameX, 1, false, 1.0f);
}

void MonsterDie::Start()
{
	Play();

	Monster* monster = (Monster*)target;
	if (monster->GetIsBoss())
	{
		if (!Audio::Get()->IsPlaySound("BossDie"))
			Audio::Get()->Play("BossDie");
	}
	else 
	{
		if (!Audio::Get()->IsPlaySound("MonsterDie"))
			Audio::Get()->Play("MonsterDie");
	}
}

void MonsterDie::End()
{
	target->SetActive(false);
}
