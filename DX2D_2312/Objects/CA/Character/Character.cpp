#include "Framework.h"

Character::Character()
{
    CreateActions();
    actions[curState]->Start();

    collider = new RectCollider({ 100, 100 });
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

    actions[curState]->Update();

    UpdateWorld();
    collider->UpdateWorld();
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

void Character::Move()
{

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
        BubbleManager::Get()->Spawn(GetLocalPosition(),1);
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
}

