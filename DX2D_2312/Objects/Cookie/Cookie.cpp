#include "Framework.h"

Cookie::Cookie() : GameObject(false)
{
    Observer::Get()->AddIntEvent("SetAction", bind(&Cookie::SetAction, this, placeholders::_1));
    Observer::Get()->AddEvent("Landing", bind(&Cookie::Landing, this));

    CreateActions();
    actions[curState]->Start();

    collider = new RectCollider({100, 100});
    collider->SetParent(this);
    collider->SetTag("CookieBody");
    collider->Load();

    BulletManager::Get();

    outlineBuffer = new OutlineBuffer();
}

Cookie::~Cookie()
{
    for (auto action : actions)
        delete action.second;

    delete collider;

    BulletManager::Delete();
}

void Cookie::Update()
{
    Move();
    Jump();
    Attack();

    actions[curState]->Update();

    outlineBuffer->GetData().imageSize = actions[curState]->GetCurClip()->GetCurFrame()->GetSize();

    UpdateWorld();
    collider->UpdateWorld();
}

void Cookie::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    outlineBuffer->SetPS(1);
    actions[curState]->Render();

    collider->Render();
}

void Cookie::PostRender()
{
    collider->RenderUI();
}

void Cookie::Move()
{
    if (curState >= JUMP_UP) return;

    bool isMove = false;

    isMove |= KEY->Press('D');
    isMove |= KEY->Press('A');

    isMove ? SetAction(RUN) : SetAction(IDLE);
}

void Cookie::Jump()
{
    if (curState >= RANGE) return;

    if (KEY->Down('W'))
    {
        if (jumpCount == 0)
        {
            SetAction(JUMP_UP);            
        }
        else if(jumpCount == 1)
        {
            SetAction(JUMP_DOUBLE);            
        }

        jumpCount++;
    }
}

void Cookie::Attack()
{
    if (curState >= RANGE) return;

    if (KEY->Down(VK_LBUTTON))
        SetAction(RANGE);

    if (KEY->Down(VK_RBUTTON))
        SetAction(MELEE);
}

void Cookie::Landing()
{
    SetAction(IDLE);

    jumpCount = 0;
}

void Cookie::SetAction(int state)
{
    if (curState == state) return;

    curState = (State)state;
    actions[curState]->Start();
}

void Cookie::CreateActions()
{
    actions[IDLE] = new CookieAction("Cookie_Idle.xml", true, 0.7f);
    actions[RUN] = new CookieRun(this);
    actions[JUMP_UP] = new CookieJumpUp(this);    
    actions[JUMP_DOWN] = new CookieJumpDown(this);    
    actions[JUMP_DOUBLE] = new CookieJumpDouble(this);        
    actions[RANGE] = new CookieRange(this);
    actions[MELEE] = new CookieMelee(this);
}