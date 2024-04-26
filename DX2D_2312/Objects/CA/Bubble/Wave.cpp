#include "Framework.h"

Wave::Wave()
{
	SetActive(false);

	CreateActions();

	collider = new RectCollider({ Tile::TILE_SIZE - 10.0f, Tile::TILE_SIZE - 10.0f });
	collider->SetParent(this);
}

Wave::~Wave()
{
	delete collider;

	//Áú¹®¿é
	for (auto& pair : actions) 
		delete pair.second;
	actions.clear();
}

void Wave::Update()
{
	if (!this->IsActive()) return;

	actions[curState]->Update();
	UpdateWorld();
	collider->UpdateWorld();
}

void Wave::Render()
{
	if (!this->IsActive()) return;

	collider->Render();
	actions[curState]->Render();
}

float Wave::GetDepth()
{
	return collider->Top();
}

void Wave::CreateActions()
{
	Action* action = new Action();
	action->LoadClip(ToWString(PATH) + L"Wave_Start.png", 11, 1, false, 2.6f);
	action->GetClip(0)->SetEvent([this]() {TileManager::Get()->SetIdxBgTileType(posTileIdx, Tile::BASIC); }, 7);
	action->GetClip(0)->SetEvent([this]() {this->SetActive(false);});
	actions[START] = action;

	action = new Action();
	action->LoadClip(ToWString(PATH) + L"Wave_End.png", 11, 1, false, 2.6f);
	action->GetClip(0)->SetEvent([this]() {TileManager::Get()->SetIdxBgTileType(posTileIdx, Tile::BASIC);}, 7);
	action->GetClip(0)->SetEvent([this]() {this->SetActive(false);});
	actions[END] = action;
}

void Wave::Spawn(const Vector2& pos, Direction direction, State state)
{
	SetActive(true);
	SetAction(state);

	switch (direction)
	{
	case Wave::R:
		SetLocalRotation(0, 0, 0);
		break;
	case Wave::L:
		SetLocalRotation(0, 0, XM_PI);
		break;
	case Wave::U:
		SetLocalRotation(0, 0, XM_PI * 0.5f);
		break;
	case Wave::D:
		SetLocalRotation(0, 0, -XM_PI * 0.5f);
		break;
	default:
		break;
	}
}

void Wave::SetAction(int state)
{
	curState = (State)state;
	actions[curState]->Start();
}
