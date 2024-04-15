#include "Framework.h"

Bubble::Bubble()
{
	SetActive(false);

	//action.push_back(LoadClip(ToWString(PATH) + L"Bazzi/Stand.png", 1, 1, false));

}

Bubble::~Bubble()
{
	delete collider;
}

void Bubble::Update()
{
	UpdateWorld();
	collider->UpdateWorld();
}

void Bubble::Render()
{
	collider->Render();
}

void Bubble::Spawn(const Vector2& pos, int speed)
{
	SetActive(true);
	this->power = power;

	SetLocalPosition(pos);

	UpdateWorld();
}
