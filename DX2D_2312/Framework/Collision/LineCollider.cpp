#include "Framework.h"

LineCollider::LineCollider(Vector2 startPos, Vector2 endPos)
{
    tag = "Line";
    type = Type::LINE;

    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.emplace_back(startPos.x, startPos.y);
    vertices.emplace_back(endPos.x, endPos.y);
    
    mesh->CreateMesh();
}

bool LineCollider::IsPointCollision(Vector2 point)
{
    return false;
}

bool LineCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    return false;
}

bool LineCollider::IsCircleCollision(CircleCollider* circle)
{
    return false;
}
