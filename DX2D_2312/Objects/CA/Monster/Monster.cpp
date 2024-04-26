#include "Framework.h"

Monster::Monster(int key, float speed, bool isBubble, int hp) 
    : Character(), key(key), speed(speed), isBubble(isBubble), hp(hp)
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

void Monster::Hit()
{
    hp--;
    if (hp <= 0)
        SetAction(DIE);
    else
        SetAction(HIT);
}

void Monster::Die()
{
    if (curState == DIE|| curState == HIT) return;

    Tile* tile = TileManager::Get()->GetNearPosTileState(collider->GetGlobalPosition());

    if (!tile) return;

    if (tile->GetType() == Tile::ATTACK)
        SetAction(HIT);
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
    if(hp >= 2)
	    actions[HIT] = new MonsterHit(this, key);
}
