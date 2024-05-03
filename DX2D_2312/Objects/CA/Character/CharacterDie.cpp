#include "Framework.h"

CharacterDie::CharacterDie(Transform* target)
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Bazzi/Die2.png", 11, 1, false, 1.0f);
}

void CharacterDie::Start()
{
	Play();

	if (!Audio::Get()->IsPlaySound("CharacterDie"))
	{
		Audio::Get()->Play("CharacterDie");
	}
}

void CharacterDie::End()
{
	StageManager::Get()->Gameover();
}
