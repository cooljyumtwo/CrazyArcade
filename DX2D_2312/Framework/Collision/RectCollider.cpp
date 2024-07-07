#include "Framework.h"

RectCollider::RectCollider(Vector2 size) : size(size) // 오프셋 초기화
{
    tag = "Rect";
    type = Type::RECT;

    Vector2 halfSize = size * 0.5f;

    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.emplace_back(-halfSize.x, +halfSize.y);
    vertices.emplace_back(+halfSize.x, +halfSize.y);
    vertices.emplace_back(+halfSize.x, -halfSize.y);
    vertices.emplace_back(-halfSize.x, -halfSize.y);
    vertices.emplace_back(-halfSize.x, +halfSize.y);

    mesh->CreateMesh();
}

//Cross 방식
bool RectCollider::IsPointCollision(Vector2 point)
{
    bool isLeftTop = IsBetweenPoint(LeftTop(), RightTop(), LeftBottom(), point);
    bool isRightBottom = IsBetweenPoint(RightBottom(), RightTop(), LeftBottom(), point);
    bool isRightTop = IsBetweenPoint(RightTop(), LeftTop(), RightBottom(), point);

    return isLeftTop && isRightBottom && isRightTop;
}

bool RectCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    if (overlap)
        return IsAABB(rect, overlap);

    return IsOBB(rect);
}

bool RectCollider::IsCircleCollision(CircleCollider* circle)
{
    ObbDesc obb = GetObb();

    Vector2 direction = obb.pos - circle->GetGlobalPosition();

    float x = abs(Vector2::Dot(direction, obb.axis[0]));
    float y = abs(Vector2::Dot(direction, obb.axis[1]));

    if (x > obb.halfSize.x + circle->Radius()) return false;
    if (y > obb.halfSize.y + circle->Radius()) return false;

    if (x < obb.halfSize.x) return true;
    if (y < obb.halfSize.y) return true;

    Vector2 temp = Vector2(x, y) - obb.halfSize;

    return circle->Radius() > temp.Magnitude();
}

Vector2 RectCollider::LeftTop()
{
    Vector2 edge = Vector2(-size.x, +size.y) * 0.5f;

    return (edge + offset) * world;
}

Vector2 RectCollider::LeftBottom()
{
    Vector2 edge = Vector2(-size.x, -size.y) * 0.5f;

    return (edge + offset) * world;
}

Vector2 RectCollider::RightTop()
{
    Vector2 edge = Vector2(+size.x, +size.y) * 0.5f;

    return (edge + offset) * world;
}

Vector2 RectCollider::RightBottom()
{
    Vector2 edge = Vector2(+size.x, -size.y) * 0.5f;

    return (edge + offset) * world;
}

float RectCollider::Left()
{
    float minLeft = min(LeftTop().x, LeftBottom().x);
    float minRight = min(RightTop().x, RightBottom().x);

    return min(minLeft, minRight);
}

float RectCollider::Right()
{
    float maxLeft = max(LeftTop().x, LeftBottom().x);
    float maxRight = max(RightTop().x, RightBottom().x);

    return max(maxLeft, maxRight);
}

float RectCollider::Top()
{
    float maxLeft = max(LeftTop().y, LeftBottom().y);
    float maxRight = max(RightTop().y, RightBottom().y);

    return max(maxLeft, maxRight);
}

float RectCollider::Bottom()
{
    float minLeft = min(LeftTop().y, LeftBottom().y);
    float minRight = min(RightTop().y, RightBottom().y);

    return min(minLeft, minRight);
}

RectCollider::ObbDesc RectCollider::GetObb()
{
    obbDesc.pos = GetGlobalPosition();
    obbDesc.halfSize = Half();

    obbDesc.axis[0] = GetRight();
    obbDesc.axis[1] = GetUp();

    return obbDesc;
}

void RectCollider::SetSize(Vector2 size)
{
    this->size = size;

    Vector2 halfSize = size * 0.5f;

    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.clear();

    vertices.emplace_back(-halfSize.x + offset.x, +halfSize.y + offset.y);
    vertices.emplace_back(+halfSize.x + offset.x, +halfSize.y + offset.y);
    vertices.emplace_back(+halfSize.x + offset.x, -halfSize.y + offset.y);
    vertices.emplace_back(-halfSize.x + offset.x, -halfSize.y + offset.y);
    vertices.emplace_back(-halfSize.x + offset.x, +halfSize.y + offset.y);

    mesh->UpdateVertices();
}

bool RectCollider::IsBetweenPoint(const Vector2& start, const Vector2& end1, const Vector2& end2, const Vector2& point)
{
    Vector2 A = end1 - start;
    Vector2 B = end2 - start;

    Vector2 startToPoint = point - start;

    float crossA = Vector2::Cross(A, startToPoint);
    float crossB = Vector2::Cross(B, startToPoint);

    return crossA * crossB < 0.0f;
}

bool RectCollider::IsAABB(RectCollider* rect, Vector2* overlap)
{
    float left = max(Left(), rect->Left());
    float right = min(Right(), rect->Right());
    float bottom = max(Bottom(), rect->Bottom());
    float top = min(Top(), rect->Top());

    overlap->x = right - left;
    overlap->y = top - bottom;

    return overlap->x > 0 && overlap->y > 0;
}

bool RectCollider::IsOBB(RectCollider* rect)
{
    ObbDesc obbA = GetObb();
    ObbDesc obbB = rect->GetObb();

    if (IsSeperate(obbA.axis[0], obbA, obbB)) return false;
    if (IsSeperate(obbA.axis[1], obbA, obbB)) return false;
    if (IsSeperate(obbB.axis[0], obbA, obbB)) return false;
    if (IsSeperate(obbB.axis[1], obbA, obbB)) return false;

    return true;
}

bool RectCollider::IsSeperate(const Vector2& seperateAxis, ObbDesc box1, ObbDesc box2)
{
    float d = abs(Vector2::Dot(seperateAxis, box1.pos - box2.pos));

    Vector2 right = box1.axis[0] * box1.halfSize.x;
    Vector2 up = box1.axis[1] * box1.halfSize.y;

    float a = abs(Vector2::Dot(seperateAxis, right)) + abs(Vector2::Dot(seperateAxis, up));

    right = box2.axis[0] * box2.halfSize.x;
    up = box2.axis[1] * box2.halfSize.y;

    float b = abs(Vector2::Dot(seperateAxis, right)) + abs(Vector2::Dot(seperateAxis, up));

    return d > (a + b);
}
