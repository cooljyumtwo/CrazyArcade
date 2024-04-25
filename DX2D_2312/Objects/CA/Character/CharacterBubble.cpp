#include "Framework.h"

CharacterBubble::CharacterBubble(Transform* target) 
{
	SetTarget(target);

	LoadClip(ToWString(PATH) + L"Bazzi/Bubble.png", 4, 1, false, 0.3f);
}

void CharacterBubble::Update()
{
	CharacterAction::Update();

	Move();
    Alive();

	target->UpdateWorld();
}

void CharacterBubble::Start()
{
    Action::Start();

    SetCompass(Compass::E);
}

void CharacterBubble::End()
{
    Character* character = (Character*)target;
    character->SetAction(Character::DIE);
}

void CharacterBubble::Move()
{
    velocity = { 0, 0 };

    if (KEY->Press('D'))
    {
        velocity.x = 1.0f;
    }
    if (KEY->Press('A'))
    {
        velocity.x = -1.0f;
    }
    if (KEY->Press('W'))
    {
        velocity.y = 1.0f;
    }
    if (KEY->Press('S'))
    {
        velocity.y = -1.0f;
    }
    target->Translate(velocity * moveSpeed * 0.5f * DELTA);

    Character* character = (Character*)target;
    TileManager::Get()->PushPlayer(character);
}

void CharacterBubble::Alive()
{
    if (KEY->Down(VK_CONTROL))
    {
        Character* character = (Character*)target;
        character->SetAction(Character::ALIVE);
    }
}

