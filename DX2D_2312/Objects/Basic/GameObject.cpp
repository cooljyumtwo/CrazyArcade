#include "Framework.h"

GameObject::GameObject()
{
	material = new Material();
	worldBuffer = new MatrixBuffer();

	collider = new RectCollider({ Tile::TILE_SIZE - 10.0f, Tile::TILE_SIZE - 10.0f });
	collider->SetParent(this);
}

GameObject::~GameObject()
{
	delete collider;
	delete material;
	delete worldBuffer;
}

void GameObject::SetRender()
{
	worldBuffer->Set(world);
	worldBuffer->SetVS(0);

	material->Set();
}

float GameObject::GetDepth()
{
	return collider->Bottom();
}

bool GameObject::Compare(GameObject* obj1, GameObject* obj2)
{
	return obj1->GetDepth() > obj2->GetDepth();
}
