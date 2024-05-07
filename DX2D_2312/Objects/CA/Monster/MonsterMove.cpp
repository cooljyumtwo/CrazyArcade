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

    Monster* monster = (Monster*)target;
    if (monster->GetIsBoss())
    {
        if (!Audio::Get()->IsPlaySound("BossMove"))
            Audio::Get()->Play("BossMove");
    }


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

    if (TileManager::Get()->PushGameObject(character))
        RandomCompass();

    if (TileManager::Get()->CheckMapPosPlayer(character))
        RandomCompass();

    BubbleManager::Get()->PushPlayer(character);

}

void MonsterMove::SetMoveTime()
{
    moveTime = Random(1.0f, 5.0f);
}

void MonsterMove::RandomCompass()
{
    velocity = { 0, 0 };

    int randomCompassType = Random(0, 2);

    if (randomCompassType) //사용자 방향
    {
        Monster* monster = (Monster*)target;
        Character* player = monster->GetPlayer();

        if (!player) return;

        Vector2 distance = monster->GetGlobalPosition() - player->GetGlobalPosition();

        if (distance.x < distance.y) // 상하
        {
            if (distance.y > 0)
                SetCompass(Compass::S); // 플레이어가 몬스터보다 위에 있음
            else
                SetCompass(Compass::N); // 플레이어가 몬스터보다 아래에 있음
        }
        else // 좌우
        {
            if (distance.x > 0)
                SetCompass(Compass::W); // 플레이어가 몬스터보다 왼쪽에 있음
            else
                SetCompass(Compass::E); // 플레이어가 몬스터보다 오른쪽에 있음
        }
    }
    else //무작위 방향
    {
        int randomCompass = Random(0, 4); // 어디부터 체크할지 

        Vector2 curPos = target->GetGlobalPosition();
        vector<Vector2> checkPos;

        vector<Vector2> offsets = {
            Vector2{0, -1},  // 남쪽
            Vector2{0, 1},   // 북쪽
            Vector2{1, 0},   // 동쪽
            Vector2{-1, 0}   // 서쪽
        };

        checkPos.resize(offsets.size());

        FOR(offsets.size())
        {
            int idx = (i + randomCompass) % offsets.size(); // 인덱스 계산
            checkPos[i] = (curPos + offsets[idx] * Tile::TILE_SIZE); // 방향 벡터 사용
        }

        int compass = -1; // 선택된 방향
        FOR(checkPos.size())
        {
            Tile* tile = TileManager::Get()->GetNearPosTileState(checkPos[i]);

            if (!tile) continue; // 타일이 유효하지 않으면 다음으로 넘어감

            if (tile->GetType() == Tile::BASIC)
            {
                compass = (i + randomCompass) % offsets.size(); // 선택된 방향 계산
                switch (compass) // compass로 수정
                {
                case 0: // 남쪽
                    SetCompass(Compass::S);
                    break;
                case 1: // 북쪽
                    SetCompass(Compass::N);
                    break;
                case 2: // 동쪽
                    SetCompass(Compass::E);
                    break;
                case 3: // 서쪽
                    SetCompass(Compass::W);
                    break;
                default:
                    break;
                }
                return;
            }
        }
    }
}

void MonsterMove::End()
{
    
}
