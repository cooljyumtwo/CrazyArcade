#include "Framework.h"

BossHit::BossHit(Transform* target, int key, int max_frameX)
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Hit.png", max_frameX, 1, false);
}

void BossHit::Start()
{
	if (!Audio::Get()->IsPlaySound("BossHit"))
		Audio::Get()->Play("BossHit");

	CharacterAction::Start();
}

void BossHit::End()
{
	Boss* boss = (Boss*)target;
	boss->SetAction(boss->curType);
}