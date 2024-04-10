#include "Framework.h"

Tile::Tile(Data data)
    : Quad(data.textureFile, false), data(data)
{
    SetLocalPosition(data.pos);    

    collider = new IsometricCollider({ size.x, size.y * 0.5f });
    collider->Translate(Vector2::Up() * size.y * 0.25f);
    collider->SetParent(this);
}

Tile::~Tile()
{
    delete collider;
}

void Tile::Render()
{
    if (!IsActive()) return;

    Quad::Render();
    collider->Render();    
}

void Tile::PostRender()
{
    //FONT->SetStyle("Button");
    //FONT->RenderText("Tile", CAM->WorldToScreen(GetGlobalPosition()));
}

void Tile::UpdateWorld()
{
    Transform::UpdateWorld();
    collider->UpdateWorld();
}

bool Tile::IsCompare(Tile* tile1, Tile* tile2)
{
    return tile1->GetGlobalPosition().y > tile2->GetGlobalPosition().y;
}
