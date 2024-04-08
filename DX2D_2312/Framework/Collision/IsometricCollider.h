#pragma once

class IsometricCollider : public Collider
{
public:
	IsometricCollider(Vector2 size);
	~IsometricCollider() = default;

	virtual bool IsPointCollision(Vector2 point) override;
	virtual bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
	virtual bool IsCircleCollision(CircleCollider* circle) override;	

private:
	Vector2 size;
};