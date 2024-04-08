#include "Framework.h"

Panel::Panel(wstring textureFile)
    : Quad(textureFile, false)
{
    collider = new RectCollider(size);
    collider->SetParent(this);

    SetActive(false);

    closeBtn = new Button(L"Resources/Textures/UI/boxCross.png");
    closeBtn->SetParent(this);
    closeBtn->SetLocalPosition(size * 0.5f);    
}

Panel::~Panel()
{
    delete collider;
    delete closeBtn;
}

void Panel::Update()
{
    if (!IsActive()) return;

    Drag();

    UpdateWorld();
    collider->UpdateWorld();
    closeBtn->Update();
}

void Panel::Render()
{
    if (!IsActive()) return;

    Quad::Render();
    collider->Render();
    closeBtn->Render();
}

void Panel::Drag()
{
    if (!collider->IsPointCollision(mousePos)) return;    

    if (KEY->Down(VK_LBUTTON))
        offset = mousePos - GetGlobalPosition();

    if (KEY->Press(VK_LBUTTON))
        SetGlobalPosition(mousePos - offset);
}
