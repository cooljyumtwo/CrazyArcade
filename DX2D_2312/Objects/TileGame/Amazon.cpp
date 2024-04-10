#include "Framework.h"

Amazon::Amazon()
{
    AddAction("Resources/Textures/Amazon/Idle/Idle_Bow_Body_", 4, 4);
    AddAction("Resources/Textures/Amazon/Walk/Run_Bow_Body_", 5, 4);

    actions[0]->SetState(S);
}

Amazon::~Amazon()
{
    for (Action* action : actions)
        delete action;
}

void Amazon::Update()
{
    //KeyControl();
    MouseControl();
    SetAnimState();
    Move();

    actions[curState]->Update();

    UpdateWorld();
}

void Amazon::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    actions[curState]->Render();
}

void Amazon::AddAction(string file, int frameX, int frameY)
{
    Action* action = new Action();
    
    FOR(8)
    {
        int angle = i * 45;
        wstring number = to_wstring(angle);;
        if (angle == 0)
            number = L"000";
        else if(angle < 100)
            number = L"0" + number;

        wstring actionFile = ToWString(file) + number + L".png";

        action->LoadClip(actionFile, frameX, frameY, true);
    }

    actions.push_back(action);
}

void Amazon::KeyControl()
{
    int inputCompass = 0;
    velocity = {};

    if (KEY->Press('W'))
    {
        inputCompass |= N;    
        velocity.y = 1.0f;
    }else if (KEY->Press('S'))
    {
        inputCompass |= S;
        velocity.y = -1.0f;
    }

    if (KEY->Press('D'))
    {
        inputCompass |= E;
        velocity.x = 1.0f;
    }
    else if (KEY->Press('A'))
    {
        inputCompass |= W;
        velocity.x = -1.0f;
    }

    if (inputCompass == 0)
    {
        SetState(0, compass);
    }
    else
    {        
        SetState(1, inputCompass);
    }        
}

void Amazon::MouseControl()
{
    //if (KEY->Down(VK_LBUTTON))
    //{
    //    path.insert(path.begin(), mousePos);
    //}

    if (path.empty())
    {
        velocity = {};
        return;
    }

    Vector2 destPos = path.back();

    velocity = destPos - localPosition;

    if (velocity.Magnitude() < 10.0f)
    {
        path.pop_back();
    }
    else
    {
        velocity.Normalize();
    }
}

void Amazon::SetAnimState()
{
    if (velocity.Magnitude() == 0)
    {
        SetState(0, compass);
        return;
    }

    float angle = XM_PIDIV2 - velocity.Angle();

    if (angle < 0.0f)
        angle += XM_2PI;

    float step = XM_PI / 8.0f;
    int inputCompass = NONE;

    if (angle > step && angle < step * 3)
    {
        inputCompass = NE;
    }
    else if (angle > step * 3 && angle < step * 5)
    {
        inputCompass = E;
    }
    else if (angle > step * 5 && angle < step * 7)
    {
        inputCompass = SE;
    }
    else if (angle > step * 7 && angle < step * 9)
    {
        inputCompass = S;
    }
    else if (angle > step * 9 && angle < step * 11)
    {
        inputCompass = SW;
    }
    else if (angle > step * 11 && angle < step * 13)
    {
        inputCompass = W;
    }
    else if (angle > step * 13 && angle < step * 15)
    {
        inputCompass = NW;
    }
    else
    {
        inputCompass = N;
    }

    SetState(1, inputCompass);
}

void Amazon::Move()
{
    Translate(velocity * speed * DELTA);
}

void Amazon::SetState(int state, int compass)
{
    curState = state;    
    this->compass = (Compass)compass;

    switch (compass)
    {
    case Amazon::N:
        actions[state]->SetState(0);
        break;
    case Amazon::E:
        actions[state]->SetState(2);
        break;
    case Amazon::S:
        actions[state]->SetState(4);
        break;
    case Amazon::W:
        actions[state]->SetState(6);
        break;
    case Amazon::SE:
        actions[state]->SetState(3);
        break;
    case Amazon::NE:
        actions[state]->SetState(1);
        break;
    case Amazon::SW:
        actions[state]->SetState(5);
        break;
    case Amazon::NW:
        actions[state]->SetState(7);
        break;    
    }
}
