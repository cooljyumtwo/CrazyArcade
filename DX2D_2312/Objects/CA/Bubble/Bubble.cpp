#include "Framework.h"

Bubble::Bubble()
{
	SetActive(false);

	Action* action = new Action();

	wstring actionFile = ToWString("ResourcesCA/Textures/Character/Bazzi/Run") + L".png";

	action->LoadClip(ToWString(PATH) + L"Stand.png", 3, 1, true);

	actions[STAND] = action;
	//actions[STAND]->SetParent(this);

	collider = new RectCollider({ Tile::TILE_SIZE-10.0f, Tile::TILE_SIZE - 10.0f });
	collider->SetParent(this);

}

Bubble::~Bubble()
{
	delete collider;
}

void Bubble::Update()
{
	if (!this->IsActive()) return;

	UpdateWorld();
	collider->UpdateWorld();
	actions[state]->Update();
	
}

void Bubble::Render()
{
	if (!this->IsActive()) return;

	collider->Render();
	actions[state]->Render();
}

void Bubble::Spawn(const Vector2& pos, int speed)
{
	Translate(pos);

	UpdateWorld();
	collider->UpdateWorld();

	Tile* tile = TileManager::Get()->SetNearPosState(collider, Tile::OBSTACLE);

	if (!tile) return;

	SetActive(true);
	this->power = power;
	this->SetGlobalPosition(tile->GetGlobalPosition());
}
