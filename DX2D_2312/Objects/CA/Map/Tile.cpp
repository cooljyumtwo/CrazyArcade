#include "Framework.h"

float Tile::TILE_SIZE = 40.0f;

Tile::Tile(Data data)
    : Quad(data.textureFile, false), data(data)
{
    SetLocalPosition(data.pos);    

    collider = new RectCollider(size);
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

    string fps = to_string(data.type);
    Font::Get()->RenderText(fps, GetGlobalPosition());
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
