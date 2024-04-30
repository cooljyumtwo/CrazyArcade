#include "Framework.h"

CharacterDie::CharacterDie(Transform* target)
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Bazzi/Die.png", 6, 1, false, 1.0f);
}

void CharacterDie::End()
{
	target->SetActive(false);
	StageManager::Get()->Gameover();
}
