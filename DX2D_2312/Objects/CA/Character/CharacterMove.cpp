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

    Character* character = (Character*)target;

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

    int speed = (character->GetStat().speed > MAX_SPEED) ? MAX_SPEED : character->GetStat().speed;
    target->Translate(velocity * speed * moveSpeed * DELTA );

    TileManager::Get()->PushGameObject(character, true);
    TileManager::Get()->CheckMapPosPlayer(character);

    Player* player = (Player*)target;
    Bubble* bubble = BubbleManager::Get()->PushPlayer(character, player->GetIsBubblePush());
    if (bubble)
    {
        playTime += DELTA;
        if (playTime < MAX_PUSH_TIME)
        {
            bubble->SetIsPush(true);
        }
    }
    else 
    {
        playTime = 0.0f;
    }

    ItemManager::Get()->Collision(character);

    if (compass == W) velocity.x = 1.0f;
}
