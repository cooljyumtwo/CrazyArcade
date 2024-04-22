#include "Framework.h"

Item::Item()
{
    SetActive(false); 
    collider = new RectCollider({ Tile::TILE_SIZE, Tile::TILE_SIZE });
    collider->SetParent(this);
}

void Item::Update()
{
    if (!IsActive()) return;

    UpdateWorld();
    collider->UpdateWorld();
}

void Item::Spawn(const Vector2& pos, ItemData data)
{
    SetActive(true);

    isField = true;

    this->data = data;
    wstring textureFile = L"ResourcesCA/Textures/Item/" + data.textureFile;
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
    wstring textureFile = L"ResourcesCA/Textures/Item/" + data.textureFile;
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
