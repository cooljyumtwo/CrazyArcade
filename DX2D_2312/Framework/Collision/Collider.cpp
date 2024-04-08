#include "Framework.h"

Collider::Collider()
{
    material = new Material();
    material->SetVertexShader(L"Vertex.hlsl");
    material->SetPixelShader(L"Pixel.hlsl");
    material->GetColor()->SetColor(0, 1, 0);

    worldBuffer = new MatrixBuffer();        

    mesh = new Mesh<Vertex>();
}

Collider::~Collider()
{
    delete material;
    delete mesh;

    delete worldBuffer;
}

void Collider::Render()
{
    if (!IsActive()) return;

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    material->Set();
    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
}

bool Collider::IsCollision(Collider* collider, Vector2* overlap)
{
    if (!IsActive()) return false;
    if (!collider->IsActive()) return false;

    switch (collider->type)
    {
    case Collider::Type::RECT:
        return IsRectCollision((RectCollider*)collider, overlap);            
    case Collider::Type::CIRCLE:
        return IsCircleCollision((CircleCollider*)collider);        
    }

    return false;
}