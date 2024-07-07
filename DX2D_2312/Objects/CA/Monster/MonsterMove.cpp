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
        SetMoveTime();
        nearTile = nullptr;
        RandomCompass();
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

    if (TileManager::Get()->GetNearPosTileState(target->GetGlobalPosition()) == nearTile)
    {
        nearTile = nullptr;
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

    int speed = (character->GetStat().speed > MAX_SPEED) ? MAX_SPEED : character->GetStat().speed;
    target->Translate(velocity * speed * moveSpeed * DELTA);

    if (TileManager::Get()->PushGameObject(character) || TileManager::Get()->CheckMapPosPlayer(character))
    {
        RandomCompass();
    }

    BubbleManager::Get()->PushPlayer(character);
}

void MonsterMove::SetMoveTime()
{
    moveTime = Random(1.0f, 5.0f);
}

void MonsterMove::RandomCompass()
{
    if (nearTile != nullptr) return;

    velocity = { 0, 0 };

    int randomCompassType = Random(0, 3);

    Monster* monster = (Monster*)target;

    if (randomCompassType < 2) //����� ����
    {
        Character* player = monster->GetPlayer();

        if (!player) return;

        Vector2 distance = player->GetGlobalPosition() - monster->GetGlobalPosition();

        if (abs(distance.x) > abs(distance.y)) // �¿�� �� �� �Ÿ�
        {
            if (distance.x > 0)
                SetCompass(Compass::E); // �÷��̾ ������ �����ʿ� ����
            else
                SetCompass(Compass::W); // �÷��̾ ������ ���ʿ� ����
        }
        else // ���Ϸ� �� �� �Ÿ�
        {
            if (distance.y > 0)
                SetCompass(Compass::N); // �÷��̾ ������ ���� ����
            else
                SetCompass(Compass::S); // �÷��̾ ������ �Ʒ��� ����
        }
    }
    else //������ ����
    {
        int randomCompass = Random(0, 4); // ������ üũ���� 

        Vector2 curPos = target->GetGlobalPosition();
        vector<Vector2> checkPos;

        vector<Vector2> offsets = {
            Vector2{0, -1},  // ����
            Vector2{0, 1},   // ����
            Vector2{1, 0},   // ����
            Vector2{-1, 0}   // ����
        };

        checkPos.resize(offsets.size());

        FOR(offsets.size())
        {
            int idx = (i + randomCompass) % offsets.size(); // �ε��� ���
            checkPos[i] = (curPos + offsets[idx] * Tile::TILE_SIZE); // ���� ���� ���
        }

        int compass = -1; // ���õ� ����
        FOR(checkPos.size())
        {
            Tile* tile = TileManager::Get()->GetNearPosTileState(checkPos[i]);

            if (!tile) continue; // Ÿ���� ��ȿ���� ������ �������� �Ѿ

            if (tile->GetType() == Tile::BASIC)
            {
                compass = (i + randomCompass) % offsets.size(); // ���õ� ���� ���
                nearTile = tile;
                Vector2 tileIdx = tile->GetCurIdx();

                switch (compass) // compass�� ����
                {
                case 0: // ����
                    SetCompass(Compass::S);
                    break;
                case 1: // ����
                    SetCompass(Compass::N);
                    break;
                case 2: // ����
                    SetCompass(Compass::E);
                    break;
                case 3: // ����
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
