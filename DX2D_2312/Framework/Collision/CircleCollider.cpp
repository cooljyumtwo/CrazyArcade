#include "Framework.h"

CircleCollider::CircleCollider(float radius) : radius(radius)
{
    tag = "Circle";
    type = Type::CIRCLE;

    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.reserve(VERTEX_COUNT + 1);

    float stepAngle = XM_2PI / VERTEX_COUNT;    
    
    FOR(VERTEX_COUNT + 1)
    {        
        float x = cos(stepAngle * i) * radius;
        float y = sin(stepAngle * i) * radius;

        vertices.emplace_back(x, y);
    }    
    
    mesh->CreateMesh();
}

bool CircleCollider::IsPointCollision(Vector2 point)
{
    if (!IsActive()) return false;

    return Distance(GetGlobalPosition(), point) < Radius();
}

bool CircleCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    return rect->IsCircleCollision(this);
}

bool CircleCollider::IsCircleCollision(CircleCollider* circle)
{
    return Distance(GetGlobalPosition(), circle->GetGlobalPosition()) < Radius() + circle->Radius();
}
