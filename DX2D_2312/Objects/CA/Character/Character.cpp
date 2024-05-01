#include "Framework.h"

Character::Character()
{
//   collider = new RectCollider({ Tile::TILE_SIZE * 0.7f ,  Tile::TILE_SIZE * 0.6f });
    collider->SetParent(this);
    collider->SetTag("Character");
    collider->Load();
}

Character::~Character()
{
    for (auto action : actions)
        delete action.second;
}

void Character::Update()
{
    if (!IsActive()) return;

    Move();
    Attack();
    Bubble();

    actions[curState]->Update();

    UpdateWorld();    

    MonsterManager::Get()->Collision(this);
}

void Character::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    actions[curState]->Render();

    collider->Render();
}

void Character::PostRender()
{
   // collider->RenderUI();
}

float Character::GetDepth()
{
    return collider->Bottom();
}

void Character::UpdateWorld()
{
    Transform::UpdateWorld();
    collider->UpdateWorld();
}

void Character::SetInit()
{
    stat.bubbleCnt = 2;
    stat.bubblePower = 2;
    stat.speed = 2;

    SetAction(IDLE);
    SetActive(true);
}

void Character::Move()
{
    if (curState == BUBBLE || curState == ALIVE || curState == DIE) return;

    bool isMove = false;

    isMove |= KEY->Press('D');
    isMove |= KEY->Press('A');
    isMove |= KEY->Press('W');
    isMove |= KEY->Press('S');

    isMove ? SetAction(MOVE) : SetAction(IDLE);
}

void Character::Attack()
{
    if (KEY->Down(VK_SPACE) && bubbleCurCnt < stat.bubbleCnt)
    {
        BubbleManager::Get()->Spawn(GetLocalPosition(), stat.bubblePower, this);
    }
}

void Character::Bubble()
{
    if (curState == BUBBLE || curState == ALIVE || curState == DIE) return;

    Tile* tile = TileManager::Get()->GetNearPosTileState(collider->GetGlobalPosition());
    
    if (!tile) return;

    if (tile->GetType() == Tile::ATTACK)
        SetAction(BUBBLE);
}


void Character::Landing()
{
}

void Character::AddAction(string file, int frameX, int frameY)
{
    Action* action = new Action();

    wstring actionFile = ToWString("ResourcesCA/Textures/Character/Bazzi/Run") + L".png";

    action->LoadClip(actionFile, frameX, frameY, true);

    actions[MOVE] = action;
}

void Character::SetAction(int state)
{
    if (curState == state) return;

    curState = (State)state;
    actions[curState]->Start();
}

void Character::CreateActions()
{
    actions[IDLE] = new CharacterIdle();
    actions[MOVE] = new CharacterMove(this);
    actions[BUBBLE] = new CharacterBubble(this);
    actions[ALIVE] = new CharacterAlive(this);
    actions[DIE] = new CharacterDie(this);
}

