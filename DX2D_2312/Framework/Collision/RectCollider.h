#pragma once

class RectCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector2 pos;
		Vector2 axis[2];
		Vector2 halfSize;
	};

public:
	RectCollider(Vector2 size);
	~RectCollider() = default;

	virtual bool IsPointCollision(Vector2 point) override;
	virtual bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
	virtual bool IsCircleCollision(CircleCollider* circle) override;	

	Vector2 LeftTop();
	Vector2 LeftBottom();
	Vector2 RightTop();
	Vector2 RightBottom();

	float Left();
	float Right();
	float Top();
	float Bottom();

	ObbDesc GetObb();

	Vector2 Size() { return size * GetGlobalScale(); }
	Vector2 Half() { return Size() * 0.5f; }	

	void SetSize(Vector2 size);

private:
	bool IsBetweenPoint(const Vector2& start, const Vector2& end1, const Vector2& end2, const Vector2& point);

	bool IsAABB(RectCollider* rect, Vector2* overlap);
	bool IsOBB(RectCollider* rect);

	bool IsSeperate(const Vector2& seperateAxis, ObbDesc box1, ObbDesc box2);

private:
	Vector2 size;

	ObbDesc obbDesc;
};