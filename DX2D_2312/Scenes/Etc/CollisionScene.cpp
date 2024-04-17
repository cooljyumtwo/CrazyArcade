#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	//colliders.push_back(new RectCollider({ 100, 200 }));	
	//colliders.back()->SetLocalPosition(CENTER);
	//
	//colliders.push_back(new CircleCollider(100));
	//colliders.push_back(new CircleCollider(50));
	//colliders.back()->SetTag("Circle2");	
	//colliders.back()->SetLocalPosition(CENTER);

	//colliders.push_back(new RectCollider({ 200, 100 }));	
	//colliders.back()->SetLocalPosition(CENTER);
	//colliders.back()->SetTag("Rect2");

	colliders.push_back(new IsometricCollider({ 100, 200 }));
	colliders.back()->SetLocalPosition(CENTER);
}

CollisionScene::~CollisionScene()
{
	for (Collider* collider : colliders)
		delete collider;
}

void CollisionScene::Update()
{
	if (colliders[0]->IsPointCollision(mousePos))
	{
		colliders[0]->GetColor()->SetColor(1, 0, 0);
	}
	else
	{
		colliders[0]->GetColor()->SetColor(0, 1, 0);
	}

	//Vector2 overlap;

	//if (colliders[0]->IsCollision(colliders[1]))
	//{
	//	colliders[0]->GetColor()->SetColor(1, 0, 0);
	//	colliders[1]->GetColor()->SetColor(1, 0, 0);
	//}
	//else
	//{
	//	colliders[0]->GetColor()->SetColor(0, 1, 0);
	//	colliders[1]->GetColor()->SetColor(0, 1, 0);
	//}

	for (Collider* collider : colliders)
		collider->UpdateWorld();
}

void CollisionScene::Render()
{
	for (Collider* collider : colliders)
		collider->Render();
}

void CollisionScene::PostRender()
{
	for (Collider* collider : colliders)
		collider->RenderUI();
}
