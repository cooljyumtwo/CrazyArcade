#include "Framework.h"

BossAttack::BossAttack(Transform* target, int key, int max_frameX)
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Attack.png", max_frameX, 1, false);
}

void BossAttack::End()
{
	Boss* boss = (Boss*)target;
	//boss->SetAction(Boss::MOVE);
}


