#include "Framework.h"

Button::Button(wstring textureFile, bool isAdd) : Quad(textureFile, isAdd)
{
    collider = new RectCollider(size);
    collider->SetParent(this);
}

Button::~Button()
{
    delete collider;
}

void Button::Update()
{
    if (!IsActive()) return;

    ClickEvent();    

    UpdateWorld();    
}

void Button::Render()
{
    if (!IsActive()) return;

    Quad::Render();
    collider->Render();

    if (text.size() == 0) return;

    Font::Get()->SetColor(textColor);
    Font::Get()->SetStyle(textStyle);
    Font::Get()->RenderText(text, GetGlobalPosition());
}

void Button::UpdateWorld()
{
    Transform::UpdateWorld();
    collider->UpdateWorld();
}

void Button::ClickEvent()
{
    if (collider->IsPointCollision(mousePos))
    {
        if (KEY->Down(VK_LBUTTON))
            isDownCheck = true;

        if (KEY->Press(VK_LBUTTON))
            state = DOWN;
        else
            state = OVER;

        if (isDownCheck && KEY->Up(VK_LBUTTON))
        {
            if (clickEvent)
                clickEvent();

            if (clickIntParamEvent)
                clickIntParamEvent(intParam);

            if (clickObjectParamEvent)
                clickObjectParamEvent(objectParam);

            isDownCheck = false;
        }
    }
    else
    {
        state = NORMAL;

        if (KEY->Up(VK_LBUTTON))
            isDownCheck = false;
    }

    switch (state)
    {
    case Button::NORMAL:
        material->GetColor()->SetColor(NORMAL_COLOR);
        break;
    case Button::OVER:
        material->GetColor()->SetColor(OVER_COLOR);
        break;
    case Button::DOWN:
        material->GetColor()->SetColor(DOWN_COLOR);
        break;
    default:
        break;
    }
}
