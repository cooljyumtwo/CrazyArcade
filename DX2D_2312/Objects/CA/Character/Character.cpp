#include "Framework.h"

Character::Character()
{
    CreateActions();
    actions[curState]->Start();

    collider = new RectCollider({ Tile::TILE_SIZE * 0.5f , Tile::TILE_SIZE * 0.5f });
    collider->Translate(Vector2::Down() * Tile::TILE_SIZE * 0.4f);
    collider->SetParent(this);
    collider->SetTag("Character");
    collider->Load();

    BubbleManager::Get();
}

Character::~Character()
{
    for (auto action : actions)
        delete action.second;

    delete collider;

    BubbleManager::Delete();
}

void Character::Update()
{
    Move();
    Jump();
    Attack();
    Bubble();

    actions[curState]->Update();

    UpdateWorld();    
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
    collider->RenderUI();
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

void Character::Jump()
{

}

void Character::Attack()
{
    if (KEY->Down(VK_SPACE))
        BubbleManager::Get()->Spawn(GetLocalPosition(), 1); 
}

void Character::Bubble()
{
    if (curState == BUBBLE || curState == ALIVE || curState == DIE) return;

    Tile* tile = TileManager::Get()->GetNearPosTileState(collider->GetGlobalPosition());
    if (tile->GetType() == Tile::ATTACK)
    {
        SetAction(BUBBLE);
    }
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

