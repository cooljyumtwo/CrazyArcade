#include "Framework.h"

Wave::Wave()
{
	SetActive(false);

	CreatActions();

	collider = new RectCollider({ Tile::TILE_SIZE - 10.0f, Tile::TILE_SIZE - 10.0f });
	collider->SetParent(this);
}

Wave::~Wave()
{
	delete collider;
}

void Wave::Update()
{
	if (!this->IsActive()) return;


	UpdateWorld();
	collider->UpdateWorld();
	actions[curState]->Update();

}

void Wave::Render()
{
	if (!this->IsActive()) return;

	collider->Render();
	actions[curState]->Render();
}

void Wave::CreatActions()
{
	Action* action = new Action();
	action->LoadClip(ToWString(PATH) + L"Wave_Start.png", 11, 1, true);
	//action->GetClip(0)->SetEvent([this]() {
	//	SetActive(false);
	//	});
	actions[START] = action;

	action = new Action();
	action->LoadClip(ToWString(PATH) + L"Wave_End.png", 11, 1, false);
	//action->GetClip(0)->SetEvent([this]() {
	//	SetActive(false);
	//	});
	actions[END] = action;

}

void Wave::Spawn(const Vector2& pos, int power, State state)
{
	SetGlobalPosition(pos+Tile::TILE_SIZE);
	UpdateWorld();
	collider->UpdateWorld();

	//Tile* tile = TileManager::Get()->SetNearPosState(pos, Tile::OBSTACLE);

	//if (!tile) return;

	SetActive(true);
	SetAction(state);
	//actions[state]->Start();
	//this->power = power;
	////this->SetGlobalPosition(tile->GetGlobalPosition());

	//curState = state;
	//actions[curState]->Start();
}

//
//float Wave::GetDepth()
//{
//	return collider->Bottom();
//}

void Wave::SetAction(int state)
{
	if (curState == state) return;

	curState = (State)state;
	actions[curState]->Start();
}
