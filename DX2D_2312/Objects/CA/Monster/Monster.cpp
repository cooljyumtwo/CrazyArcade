#include "Framework.h"

Monster::Monster(int key, float speed, bool isBubble, int hp, bool isBoss) 
    : Character(), key(key), speed(speed), isBubble(isBubble), hp(hp),isBoss(isBoss)
{
    SetActive(false);

    CreateActions();

    curState = MOVE;
}

Monster::~Monster()
{
    for (auto action : actions)
        delete action.second;
}

void Monster::Update()
{
    if (!IsActive()) return;

    actions[curState]->Update();

    UpdateWorld();

    CheckTileHit();

    RemoveHitColliders();
}

void Monster::CheckTileHit()
{
    if (curState == DIE) return;

    Tile* tile = TileManager::Get()->GetNearPosTileState(GetCollider()->GetGlobalPosition());

    if (!tile) return;

    if (tile->GetType() == Tile::ATTACK)
    {
        Hit(tile->GetCollider());
    }
}

bool Monster::CheckHitCollider(Collider* collider)
{
    for (Collider* hitCollider : hitColliders)
    {
        if (hitCollider == collider)
            return false;
    }

    hitColliders.push_back(collider);
    return true;
}

void Monster::Hit(Collider* collider)
{
    if(!CheckHitCollider(collider)) return;

    hp--;

    if (hp <= 0)
    {        
        if (isBubble)
            SetAction(BUBBLE);
        else
            Die();
    }
    else 
    {
        SetAction(HIT);
    }
}

void Monster::Die()
{
    SetAction(DIE);
    MonsterManager::Get()->AddKillMonster(isBoss);
}

void Monster::Spawn(const Vector2& pos)
{
    SetActive(true);
    SetGlobalPosition(pos);
}

void Monster::RemoveHitColliders()
{
    vector<Collider*>::iterator iter = hitColliders.begin();

    for (; iter != hitColliders.end();)
    {
        if (collider->IsCollision(*iter))
        {
            iter++;
        }
        else
        {
            iter = hitColliders.erase(iter);
        }
    }
}

void Monster::Collision(Character* character)
{
    if (curState == DIE) return;

    player = character;
    if (collider->IsCollision(character->GetCollider()))
    {
        if (curState == BUBBLE)
            Die();
        else
            character->SetAction(DIE);
    }
}

void Monster::CreateActions()
{
    actions.clear();

	actions[MOVE] = new MonsterMove(this, key, speed);
	actions[DIE] = new MonsterDie(this, key);

    if(hp >= 2)
	    actions[HIT] = new MonsterHit(this, key);

    if (isBubble)
        actions[BUBBLE] = new MonsterBubble(this, key);

    SetColliderSize(actions[MOVE]->GetClip(0)->GetCurFrame()->GetSize());
}
