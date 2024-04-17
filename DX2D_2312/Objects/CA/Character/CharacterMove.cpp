#include "Framework.h"

CharacterMove::CharacterMove(Transform* target)
{
    SetTarget(target);

    LoadClip(ToWString(PATH) + L"Bazzi/Down.png", 1, 5, true);
    LoadClip(ToWString(PATH) + L"Bazzi/Up.png", 5, 1, true);
    LoadClip(ToWString(PATH) + L"Bazzi/Run.png", 4, 1, true);
    LoadClip(ToWString(PATH) + L"Bazzi/Run.png", 4, 1, true);


    frontCollider = new RectCollider({ Tile::TILE_SIZE, Tile::TILE_SIZE });
    frontCollider->SetParent(target);
    frontCollider->SetTag("CharacterFront");
    frontCollider->GetColor()->SetColor(1.0f, 0.0f, 0.0f);
}

void CharacterMove::Update()
{
    CharacterAction::Update();

    Move();

    target->UpdateWorld();
    frontCollider->UpdateWorld();
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

    target->Translate(velocity * MOVE_SPEED * DELTA);

    TileManager::Get()->PushPlayer(character, velocity);

    if (compass == W) velocity.x = 1.0f;
    frontCollider->SetLocalPosition(character->GetCollider()->GetLocalPosition() + velocity * Tile::TILE_SIZE);
}

void CharacterMove::Render()
{
    CharacterAction::Render();
    frontCollider->Render();
}
