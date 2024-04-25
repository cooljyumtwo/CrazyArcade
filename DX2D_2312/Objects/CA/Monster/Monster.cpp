#include "Framework.h"

Monster::Monster(int key, float speed, bool isBubble) 
    : Character(), key(key), speed(speed), isBubble(isBubble)
{
    SetActive(false);

    CreateActions();
}

Monster::~Monster()
{
}

void Monster::Update()
{
    if (!IsActive()) return;

    Die();

    actions[curState]->Update();

    UpdateWorld();
}

void Monster::Die()
{
    if (curState == DIE) return;

    Tile* tile = TileManager::Get()->GetNearPosTileState(collider->GetGlobalPosition());

    if (!tile) return;

    if (tile->GetType() == Tile::ATTACK)
        SetAction(DIE);
}

void Monster::Spawn(const Vector2& pos)
{
    SetActive(true);
    SetGlobalPosition(pos);
    
    curState = MOVE;
}

void Monster::CreateActions()
{
    actions.clear();

	actions[MOVE] = new MonsterMove(this, key, speed);
	actions[DIE] = new MonsterDie(this, key);
}
