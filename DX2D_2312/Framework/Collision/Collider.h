#pragma once

class Collider : public Transform
{
protected:
	enum class Type
	{
		RECT, CIRCLE, ISOMETRIC, LINE
	};

public:
	Collider();
	~Collider();

	void Render();

	bool IsCollision(Collider* collider, Vector2* overlap = nullptr);

	virtual bool IsPointCollision(Vector2 point) = 0;
	virtual bool IsRectCollision(class RectCollider* rect, Vector2* overlap = nullptr) = 0;
	virtual bool IsCircleCollision(class CircleCollider* circle) = 0;

	ColorBuffer* GetColor() { return material->GetColor(); }

protected:
	Type type;
	
	Mesh<Vertex>* mesh;
private:
	Material* material;
	MatrixBuffer* worldBuffer;	
};