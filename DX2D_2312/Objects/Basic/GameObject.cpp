#include "Framework.h"

GameObject::GameObject(bool isAdd)
{
	material = new Material();
	worldBuffer = new MatrixBuffer();

	//if(isAdd)
		//ObjectManager::Get()->Add(this);
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

bool GameObject::Compare(GameObject* obj1, GameObject* obj2)
{
	return obj1->GetDepth() < obj2->GetDepth();
}
