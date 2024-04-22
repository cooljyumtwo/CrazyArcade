#include "Framework.h"

GameObject::GameObject()
{
	material = new Material();
	worldBuffer = new MatrixBuffer();
}

GameObject::~GameObject()
{
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
	return localPosition.y;
}

bool GameObject::Compare(GameObject* obj1, GameObject* obj2)
{
	return obj1->GetDepth() > obj2->GetDepth();
}
