#include "Framework.h"

MonsterMove::MonsterMove()
{
    SetMoveTime();
}

MonsterMove::MonsterMove(Transform* target, int key, float speed, int max_frameX)
{
    SetTarget(target);

    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Move_Down.png", max_frameX, 1, true);
    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Move_Up.png", max_frameX, 1, true);
    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Move_Right.png", max_frameX, 1, true);
    LoadClip(ToWString(PATH) + L"Monster/" + to_wstring(key) + L"/Move_Right.png", max_frameX, 1, true);

    SetMoveTime();
    SetMoveSpeed(speed);
}

void MonsterMove::Update()
{
    CharacterAction::Update();

    playTime += DELTA;

    if (playTime > moveTime)
    {
        playTime -= moveTime; 
        RandomCompass();
        SetMoveTime();
    }

    Move();

    target->UpdateWorld();
}

void MonsterMove::Move()
{
    velocity = { 0, 0 };

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
    target->Translate(velocity * speed * moveSpeed * DELTA);

    if (TileManager::Get()->PushPlayer(character))
        RandomCompass();

    if (TileManager::Get()->CheckMapPosPlayer(character))
        RandomCompass();

    BubbleManager::Get()->PushPlayer(character);

    if (compass == W) velocity.x = 1.0f;
}

void MonsterMove::SetMoveTime()
{
    moveTime = Random(1.0f, 5.0f);
}

void MonsterMove::RandomCompass()
{
    velocity = { 0, 0 };

    int randomCompass = Random(0, 4);
    Character* character = (Character*)target;
    Monster* monster = (Monster*)target;
    Character* player = monster->GetPlayer();
    Vector2 cp = character->GetGlobalPosition();
    Vector2 pp = player->GetGlobalPosition();
    Vector2 distance = cp - pp;

        if (distance.x < distance.y) //�¿�
        {
            if (distance.x > 0)
            {
                SetCompass(Compass::W); 
            }
            else
            {
                SetCompass(Compass::E);
            }
        }
        else
        {
            if (distance.y > 0)
            {
                SetCompass(Compass::S);
            }
            else
            {
                SetCompass(Compass::N);
            }
        }

    //switch (randomCompass)
    //{
    //case CharacterAction::S:
    //    SetCompass(Compass::S);
    //    break;
    //case CharacterAction::N:
    //    SetCompass(Compass::N);
    //    break;
    //case CharacterAction::E:
    //    SetCompass(Compass::E);
    //    break;
    //case CharacterAction::W:
    //    SetCompass(Compass::W);
    //    break;
    //default:
    //    break;
    //}
}
