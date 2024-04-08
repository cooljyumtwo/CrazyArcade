#include "Framework.h"

IsometricCollider::IsometricCollider(Vector2 size) : size(size)
{
    tag = "Isometric";
    type = Type::ISOMETRIC;

    Vector2 halfSize = size * 0.5f;

    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.emplace_back(-halfSize.x, 0);
    vertices.emplace_back(0, +halfSize.y);
    vertices.emplace_back(+halfSize.x, 0);
    vertices.emplace_back(0, -halfSize.y);
    vertices.emplace_back(-halfSize.x, 0);

    mesh->CreateMesh();
}

bool IsometricCollider::IsPointCollision(Vector2 point)
{
    Vector2 direction = (point - GetGlobalPosition()) / (size * 0.5f);

    float sum = abs(direction.x) + abs(direction.y);

    return sum < 1.0f;
}

bool IsometricCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    return false;
}

bool IsometricCollider::IsCircleCollision(CircleCollider* circle)
{
    return false;
}
