#include "Framework.h"

Item::Item()
{
    SetActive(false);
}

void Item::Update()
{
    if (!IsActive()) return;

    if (!isField)
        ClickEvent();

    UpdateWorld();
    collider->UpdateWorld();
}

void Item::Render()
{
    if (!IsActive()) return;

    SetLevelColor();

    Button::Render();

    if (!isField)
    {
        Font::Get()->SetColor("White");
        Font::Get()->SetStyle("Default");

        Vector2 pos = GetGlobalPosition() + Vector2(30, -30);
        Font::Get()->RenderText(to_string(count), pos);
    }    
}

void Item::Spawn(const Vector2& pos, ItemData data)
{
    SetActive(true);

    isField = true;

    this->data = data;
    wstring textureFile = L"Resources/Textures/Shooting/Item/" + data.textureFile;
    SetTexture(textureFile);
    collider->SetSize(size);

    SetLocalPosition(pos);

    UpdateWorld();
    collider->UpdateWorld();      
}

void Item::SetData(ItemData data)
{
    SetActive(true);

    isField = false;    

    this->data = data;
    wstring textureFile = L"Resources/Textures/Shooting/Item/" + data.textureFile;
    SetTexture(textureFile);
    collider->SetSize(size);
}

void Item::SetLevelColor()
{
    if (data.type == 0)
    {
        material->SetColor(1, 1, 1);
        return;
    }

    int level = data.key % 10;
    switch (level)
    {
    case 1:
        material->SetColor(1, 1, 1);
        break;
    case 2:
        material->SetColor(1, 1, 0);
        break;
    case 3:
        material->SetColor(0, 1, 0);
        break;
    case 4:
        material->SetColor(1, 0, 1);
        break;
    case 5:
        material->SetColor(1, 0, 0);
        break;
    default:
        break;
    }
}
