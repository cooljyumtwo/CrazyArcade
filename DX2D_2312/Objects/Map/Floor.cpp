#include "Framework.h"

Floor::Floor(wstring file)
    : Quad(file, false)
{
    collider = new RectCollider(size);
    collider->SetParent(this);
}

Floor::~Floor()
{
    delete collider;
}

void Floor::Update()
{
    UpdateWorld();
    collider->UpdateWorld();
}

void Floor::Render()
{
    Quad::Render();
    collider->Render();
}
