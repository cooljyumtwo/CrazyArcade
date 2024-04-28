#include "Framework.h"

BossHit::BossHit(Transform* target, int key)
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Hit.png", 2, 1, false);
}

void BossHit::End()
{
	Boss* boss = (Boss*)target;
	boss->SetAction(Boss::MOVE);
}


