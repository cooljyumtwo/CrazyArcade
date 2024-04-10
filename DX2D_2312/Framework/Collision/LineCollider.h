#pragma once

class LineCollider : public Collider
{
public:
    LineCollider(Vector2 startPos, Vector2 endPos);
            
    bool IsPointCollision(Vector2 point) override;
    bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
    bool IsCircleCollision(CircleCollider* circle) override;

private:
    Vector2 startPos, endPos;
};