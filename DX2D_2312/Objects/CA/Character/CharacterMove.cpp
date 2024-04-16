#include "Framework.h"

CharacterMove::CharacterMove(Transform* target)
{
    SetTarget(target);

    LoadClip(ToWString(PATH) + L"Bazzi/Down.png", 1, 5, true);
    LoadClip(ToWString(PATH) + L"Bazzi/Up.png", 5, 1, true);
    LoadClip(ToWString(PATH) + L"Bazzi/Run.png", 4, 1, true);
    LoadClip(ToWString(PATH) + L"Bazzi/Run.png", 4, 1, true);
}

void CharacterMove::Update()
{
    CharacterAction::Update();

    Move();

    target->UpdateWorld();
}

void CharacterMove::Move()
{
    velocity = { 0, 0 };

    if (KEY->Press('D'))
    {
        SetCompass(Compass::E);
    }
    if (KEY->Press('A'))
    {
        SetCompass(Compass::W);
    }
    if (KEY->Press('W'))
    {
        SetCompass(Compass::N);
    }
    if (KEY->Press('S'))
    {
        SetCompass(Compass::S);
    }

    switch (compass)
    {
    case CharacterAction::S:        
        velocity.y = -1.0f;
        target->SetLocalScale(1, 1);
        break;
    case CharacterAction::N:
        velocity.y = 1.0f;
        target->SetLocalScale(1, 1);
        break;
    case CharacterAction::E:
        velocity.x = 1.0f;
        target->SetLocalScale(1, 1);
        break;
    case CharacterAction::W:
        velocity.x = -1.0f;
        target->SetLocalScale(-1, 1);
        break;
    default:
        break;
    }

    target->Translate(velocity * MOVE_SPEED * DELTA);
}