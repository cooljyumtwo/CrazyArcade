#include "Framework.h"

CharacterAlive::CharacterAlive(Transform* target)
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Bazzi/Live.png", 4, 1, false, 1.5f);
}

void CharacterAlive::Start()
{
	Action::Start();
}

void CharacterAlive::End()
{
	SetCompass(Compass::S);
	Character* character = (Character*)target;
	character->SetAction(Character::IDLE);
}
